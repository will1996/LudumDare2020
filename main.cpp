#include <iostream>
#include "willow.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/string_cast.hpp"
#include "Physics.hpp"
#include "AsteroidsGame.hpp"
#include "stdlib.h"




class Asteroids :public wlo::Application{
public:
    wlo::Window::Info windowInfo ;
    AsteroidsGame game;
    AsteroidsGame::Input Input;
    Asteroids():game(800,600){
       wlo::Application::Info appInfo("Asteroids",0);
        Application::initialize(appInfo);
        m_main_window->permit<wlo::MouseMessage,Asteroids,&Asteroids::recieve>(this);
        windowInfo = m_main_window->getInfo();
    }
    virtual void run() override{
        WILO_CORE_INFO("running");
        glm::mat4x4 proj = glm::ortho(-windowInfo.m_width/2,windowInfo.m_width/2,windowInfo.m_height/2,-windowInfo.m_height/2,-1.0,1.0);
        //proj[1][1]*=-1;
        m_renderer->setCamera(glm::mat4x4(1),proj);
        while(!m_shutting_down) {
            m_main_window->checkIn();
            if(m_windowResized){
                windowInfo = m_main_window->getInfo();
                glm::mat4x4 proj = glm::ortho(-windowInfo.m_width/2,windowInfo.m_width/2,windowInfo.m_height/2,-windowInfo.m_height/2,-1.0,10.0);
                //proj[1][1]*=-1;
                m_renderer->setCamera(glm::mat4x4(1),proj);
                game.resize(windowInfo.m_width,windowInfo.m_height);
                m_windowResized = false;
            }
            m_renderer->setClearColor({0,0,0,1});
            AsteroidsGame::Frame nextFrame = game.Tick(Input);
            m_renderer->pushGeometry(nextFrame.verts,nextFrame.inds,glm::mat4x4(1));
            m_renderer->beginDrawCall();




            m_renderer->submitDrawCall();
        }
    }

   virtual void recieve(const wlo::KeyboardMessage &msg) override{
       if(msg.getInfo().button==wlo::KeyCode::SPACE ) {
           if (msg.getType() == wlo::MessageType::KeyReleased)
               Input.Space = false;
           else
               Input.Space = true;
       }
       if(msg.getInfo().button==wlo::KeyCode::A )
               if(msg.getType()==wlo::MessageType::KeyReleased)
               Input.A = false;
               else
                   Input.A = true;
       if(msg.getInfo().button==wlo::KeyCode::D)
           if(msg.getType()==wlo::MessageType::KeyReleased)
               Input.D = false;
           else
               Input.D = true;
           if(msg.getInfo().button==wlo::KeyCode::S)
               if(msg.getType()==wlo::MessageType::KeyReleased)
                   Input.S = false;
               else
                    Input.S = true;
           if(msg.getInfo().button==wlo::KeyCode::W)
               if(msg.getType()==wlo::MessageType::KeyReleased)
                   Input.W = false;
               else
                    Input.W = true;
           if(msg.getInfo().button==wlo::KeyCode::T)
               if(msg.getType()==wlo::MessageType::KeyReleased)
                   Input.T = false;
               else
                    Input.T = true;
           if(msg.getInfo().button==wlo::KeyCode::G)
               if(msg.getType()==wlo::MessageType::KeyReleased)
                   Input.G = false;
               else
                    Input.G = true;

       if(msg.getInfo().button==wlo::KeyCode::ESCAPE)
               m_shutting_down = true;
   }


   void recieve(const wlo::MouseMessage & msg){
        if(msg.getType()==wlo::MessageType::MouseMoved){
            Input.mouseY = msg.getInfo().yPos.value();
            Input.mouseX = msg.getInfo().xPos.value();
            std::cout<<"updated mouse position to : "<<Input.mouseX<<","<<Input.mouseY<<std::endl;
        }
    }



    ~Asteroids(){
        Application::reclaim();
    }


};


 int main() {
     Asteroids roids;
     roids.run();
}
