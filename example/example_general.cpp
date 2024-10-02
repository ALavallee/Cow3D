#include <Cow3D/Cow3D.h>
#include <Cow3D/render/MeshBuilder.h>

int main() {

    cow::Cow3D engine("Cow3D");


    engine.getAudio().playSound(engine.getRes().getSound("chest"));
    engine.getAudio().playSound(engine.getRes().getSound("thune"));

    for (int x = 0; x < 5; ++x) {
        for (int y = 0; y < 5; ++y) {
            auto animation = engine.getScene3D().addAnimation(cow::Vec3f(x - 2, y - 2, 3),
                                                              engine.getRes().getModel("arthur"), 1);
            animation->getModel().playAnimation("running", true);
        }
    }

    auto text = engine.getScene2D().addText(cow::Vec2f(0, 200), "Cow3D !", 64);
    text->setColor(cow::Color::yellow());

    bool run = true;
    while (run) {

        SDL_Event event;
        while (engine.pollEvent(event)) {

            switch (event.type) {

                case SDL_EVENT_KEY_DOWN:
                    if (event.key.key == SDLK_ESCAPE) {
                        run = false;
                    } else if (event.key.key == SDLK_F11) {
                        engine.getWindow().flipFullscreen();
                    }
                    break;

            }

        }

        engine.update();
    }

    return 0;
}