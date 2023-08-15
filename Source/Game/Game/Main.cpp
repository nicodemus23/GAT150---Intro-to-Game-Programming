#include "Audio/AudioSystem.h"
#include "Core/Core.h"
#include "Framework/Framework.h"

#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"

#include "Player.h"
#include "Enemy.h"
#include "SpaceGame.h"

#include <iostream>
#include <vector>
#include <thread>
#include <array>
#include <list>
#include <map>

using namespace std;

class Star
{
public:
	Star(const kiko::vec2& pos, const kiko::vec2& vel) :
		m_pos{ pos },
		m_vel{ vel },
		m_color{ static_cast<Uint8>(kiko::random(256)),static_cast<Uint8>(kiko::random(256)),static_cast<Uint8>(kiko::random(256)), static_cast<Uint8>(kiko::random(1)) },
		m_targetAlpha{ 5 },
		m_alphaChangeSpeed{ 20.0f }
		//// Generate a random color for each star and vary color with (156) + 100
		////m_color{ kiko::random(156) + 100, kiko::random(156) + 100, kiko::random(156) + 100, kiko::random(255)} // Generate a random color for each star and vary color with (156) + 100
	{}



	void Update(int width, int height)
	{
		/*	m_pos += m_vel * kiko::g_time.GetDeltaTime();
			if (m_pos.x >= width) m_pos.x = 0;
			if (m_pos.y >= height) m_pos.y = 0;*/

		m_pos += m_vel * kiko::g_time.GetDeltaTime();
		if (m_pos.x >= width) m_pos.x = 0;
		if (m_pos.y >= height) m_pos.y = 0;

		//////////////////////// FINAL TWINKLE SOLUTION //////////////////////////////////////////////////
				// Interpolate alpha towards the target alpha value

		float twinkleProb = 1.0f;

		if (kiko::randomf(0.0f, 1.0f) < twinkleProb)
		{
			float alphaDiff = m_targetAlpha - m_color.a;
			float alphaChange = m_alphaChangeSpeed * kiko::g_time.GetDeltaTime();
			if (abs(alphaDiff) <= alphaChange)
			{
				m_color.a = static_cast<Uint8>(m_targetAlpha);
				m_targetAlpha = kiko::random(30); // Update the target alpha to a new random value
			}
			else
			{
				m_color.a += (alphaDiff > 0) ? alphaChange : -alphaChange;
			}
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////// first twinkle solution ///////////////////////////////
				// randomize alpha component of stars for twinkle effect 
				//if (kiko::randomf(0.1f, 5.0f) < 2.5)
				//{
				//	m_color.a = kiko::random(50); // lower value
				//}
				//else if (kiko::randomf(0.0f, 10.0f) > 2.5f)
				//{
				//	m_color.a = kiko::random(50)+ 20; // higher value
				//}
		/////////////////////////////////////////////////////////////////////////////////////////////////
	}
	/*void Draw(kiko::Renderer& renderer)
	{
		renderer.DrawPoint(m_pos.x, m_pos.y);
	}*/

	//////////////////////////////// FILLED CIRCLES //////////////////////////////////////////
	void DrawFilledCircle(kiko::Renderer& renderer)
	{
		float radius = 25.0f;
		Uint8 alpha = static_cast<Uint8>(m_color.a);
		renderer.DrawFilledCircle(m_pos.x, m_pos.y, alpha, static_cast<Uint8>(radius));
	}


	public:
		kiko::vec2 m_pos;
		kiko::vec2 m_vel;
		kiko::Color m_color;
		int m_targetAlpha;
		float m_alphaChangeSpeed;

};

template <typename T>
void print(const std::string& s, const T& container)
{
	std::cout << s << std::endl;
	for (auto element : container)
	{
		std::cout << element << " ";
	}
	std::cout << std::endl;
}



int main(int argc, char* argv[])
{


	INFO_LOG("Initialize Engine, yo...")

	kiko::MemoryTracker::Initialize();
	kiko::seedRandom((unsigned int)time(nullptr));
	kiko::setFilePath("assets");

	rapidjson::Document document;
	kiko::Json::Load("json.txt", document);

	int i1;
	kiko::Json::Read(document, "integer1", i1);
	std::cout << i1 << std::endl;
	
	int i2;
	kiko::Json::Read(document, "integer2", i2);
	std::cout << i2 << std::endl;

	std::string str;
	kiko::Json::Read(document, "string", str);
	std::cout << str << std::endl;

	bool b;
	kiko::Json::Read(document, "boolean", b);
	std::cout << b << std::endl;

	float f;
	kiko::Json::Read(document, "float", f);
	std::cout << f << std::endl;

	kiko::vec2 v2;
	kiko::Json::Read(document, "vector2", v2);
	std::cout << v2 << std::endl;



	// Initialize Game Engine // 
	kiko::g_renderer.Initialize();
	kiko::g_renderer.CreateWindow("GAT150", 800, 600);

	// Set blend render blend mode for alpha
	SDL_SetRenderDrawBlendMode(kiko::g_renderer.GetSDLRenderer(), SDL_BLENDMODE_BLEND);

	// Initialize inputSystem
	kiko::g_inputSystem.Initialize();

	// initialize AudioSystem
	kiko::g_audioSystem.Initialize();

	// create game // 
	unique_ptr<SpaceGame> game = make_unique<SpaceGame>();
	game->Initialize();

	// create texture
	//shared_ptr<kiko::Texture> texture1 = make_shared<kiko::Texture>();
	//shared_ptr<kiko::Texture> texture2 = make_shared<kiko::Texture>();
	kiko::res_t<kiko::Texture> texture = GET_RESOURCE (kiko::Texture, "test.png", kiko::g_renderer);

	//texture1->Load("AngryNerds.jpg", kiko::g_renderer);
	//texture2->Load("COMING SOON!.png", kiko::g_renderer);

	////// STARS //////
	vector<Star> stars;
	for (int i = 0; i < 1500; i++)
	{
		kiko::Vector2 pos(kiko::Vector2(kiko::random(kiko::g_renderer.GetWidth()), kiko::random(kiko::g_renderer.GetHeight())));
		kiko::Vector2 vel(kiko::randomf(10, 200), 0.0f);

		stars.push_back(Star(pos, vel));
	}

	// main game loop

	bool quit = false;
	while (!quit)
	{
		// update engine
		kiko::g_time.Tick();
		kiko::g_inputSystem.Update();
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		kiko::g_particleSystem.Update(kiko::g_time.GetDeltaTime());

		// update game
		game->Update(kiko::g_time.GetDeltaTime());

		// draw game
		kiko::g_renderer.SetColor(0, 0, 0, 0);
		kiko::g_renderer.BeginFrame();

		for (auto& star : stars)
		{
			star.Update(kiko::g_renderer.GetWidth(), kiko::g_renderer.GetHeight());
			//kiko::g_renderer.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), kiko::random(255));
			kiko::g_renderer.SetColor(static_cast<Uint8>(star.m_color.r), static_cast<Uint8>(star.m_color.g), static_cast<Uint8>(star.m_color.b), static_cast<Uint8>(star.m_color.a));
			//star.Draw(kiko::g_renderer);

			int circleRadius = 200;
			kiko::g_renderer.DrawFilledCircle(star.m_pos.x, star.m_pos.y, star.m_color.a, circleRadius);
		}



		game->Draw(kiko::g_renderer);

		// draw particles
		kiko::g_particleSystem.Draw(kiko::g_renderer);

		// draw texture
		//kiko::g_renderer.DrawTexture(texture1.get(), 250.0f, 50.0f, 0.0f, 0.5f, 0.5f);
		//kiko::g_renderer.DrawTexture(texture2.get(), 245.0f, 460.0f, 0.0f, 0.15f, 0.15f);


		kiko::g_renderer.EndFrame();
	}
	stars.clear();

	return 0;
}





// pass by value (in int main) - makes a copy
void zero(int v)
{
	v = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////

// pass by pointer version -  pass address to variable and may want to change it or not (const)
//void zero(int* v)
//{
//	*v = 0;
//}
//
//// pass by reference // may want to change it or not (const)
//void zero_ref(int& v)  // can't pass to a literal value unless you make this const (const int& v)
//{
//	v = 0;
//}
//
//void print(std::string s)
//{
//	cout << s << endl;
//}
//
//void print(std::vector<int>)
//{
//
//}



	// passed value
//int i = 5;
//zero(i);
//cout << i << endl;
//
//// passed pointer * > &
//int i = 5;
//zero(&i);
//cout << i << endl;
//
//// passed by reference 
//int i = 5;
//zero_ref(i);
//cout << i << endl;
//std::string str = "hello";
//print(str);
//
//std::vector<int> vec;
//vec.resize(10000);
//print(vec);








/////////////////////////////////////////////////////////////////////////////////////////////
/*int j = 0;
ASSERT_LOG(j,  "Pointer is null, yo.")*/
//cout << "start game...\n";

//INFO_LOG(" 'ello y'all");

//int n[4] = { 1,2,3,4 };
//print("array: 0", n);
//cout << n << endl;
//cout << n[0] << endl;
//cout << *n << endl;
//cout << (*n + 1) << endl;

//
//std::array<int, 4> na = { 1,2,3,4 };
//print("ARRAY CLASS: ", na);
//cout << na.front() << endl;
//cout << na.back() << endl;
//cout << na.max_size() << endl;
//	

//std::vector<int> nv = { 1,2,3,4 };	
//print("Vector: ", nv);
//nv.insert(nv.begin() + 2, 0);
//nv.push_back(5);
//nv.pop_back();
//nv[3] = 10;
////auto iter = std::remove(nv.begin(), nv.end(), 2);
//auto iter = nv.erase(nv.begin(), nv.end());
//print("Vector: ", nv);

//std::list<int> nl = { 1,2,3,4 };
//print("List: ", nl);
//nl.push_front(0);
//print("List: ", nl);

//std::map<std::string, int> ages;
//ages["charles"] = 17;
//ages["xane"] = 18;
//ages["jacob"] = 19;
//ages["jacob"] = 20;


/*cout << ages["jacob"] << endl;
cout << ages["xane"] << endl;*/