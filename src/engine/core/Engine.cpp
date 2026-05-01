#include "engine/core/Engine.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "engine/window/WindowFactory.h"
#include "engine/input/InputFactory.h"
#include "engine/time/TimeFactory.h"
#include "engine/renderer/RendererFactory.h"
#include "engine/renderer/Shader.h"
#include "engine/ecs/components/Meta.h"
#include "engine/ecs/components/Renderer2D.h"
#include "engine/ecs/components/Transform.h"
#include "engine/ecs/components/View.h"
#include "engine/renderer/RendererSystem.h"

// TEST VARIABLES
World* world;
EntityId esquisse;
EntityId urbain;
// END TEST VARIABLES

Engine::Engine() :
universe(std::make_unique<Universe>()){
    EWindowBackend windowBackend = EWindowBackend::GLFW;
    ERendererBackend rendererBackend = ERendererBackend::OPEN_GL;

    std::shared_ptr<WindowSettings> windowSettings = std::make_shared<WindowSettings>(1920, 1080, "Essai");
    std::shared_ptr<AWindow> window = WindowFactory::create(windowBackend, windowSettings);
    std::shared_ptr<AInput> input = InputFactory::create(windowBackend, window);
    std::shared_ptr<ATime> time = TimeFactory::create(windowBackend);
    std::shared_ptr<ARenderer> renderer = RendererFactory::create(rendererBackend);

    auto camera = std::make_shared<Camera>();
    camera->initialize(input);

    context = std::make_shared<EngineContext>(time, window, input, renderer, camera);

    initializeMocks();

}

void Engine::run() {
    auto model = glm::mat4(1.0f);
    while(context->window->isActive())
    {
        context->time->tick();
        context->input->update();
        context->camera->move(context->input, context->time);
        universe->update();
        context->window->clear();

        if (context->input->isKeyPressed(EKey::ESCAPE)) {
            context->window->close();
        }
        //model = glm::translate(glm::mat4(1.0f), universe.getWorld(0).getEntityManager()->getComponent<Component::Transform>(e1).position);
        context->window->draw();
    }
}

void Engine::quit() {
    context->window->quit();
}

void Engine::initializeMocks() {
    world = &universe->createWorld();

    // register textures
    context->renderer->registerTexture("../assets/textures/minecraft_diamond.png");
    context->renderer->registerTexture("../assets/textures/brick.jpg");

    // Create two entities to test
    if (auto entityManager = world->getEntityManager().lock()) {
        esquisse = entityManager->createEntity();
        Component::Meta meta = {"Esquisse" };
        Component::Transform transform {glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)};
        // add method in texture library to register texture and get associated id
        Component::Renderer2D renderer2D = {0, 100, 100};

        entityManager->addComponent(esquisse, meta);
        entityManager->addComponent(esquisse, transform);
        entityManager->addComponent(esquisse, renderer2D);

        urbain = entityManager->createEntity();
        Component::Meta meta1 = {"Urbain" };
        Component::Transform transform1 ={glm::vec3(5.0f, 2.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)};
        Component::Renderer2D renderer2D1 = {1, 1.0f, 1.0f};

        entityManager->addComponent(urbain, meta1);
        entityManager->addComponent(urbain, transform1);
        entityManager->addComponent(urbain, renderer2D1);
        world->registerSystem<RendererSystem>(context, world->getEntityManager());
    }
    universe->enableWorld(0);

}