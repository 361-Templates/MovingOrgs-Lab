#include "emp/math/Random.hpp"
#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"
#include "World.h"
#include "Org.h"

emp::web::Document doc{"target"};

class SwarmAnimator : public emp::web::Animate {

    emp::Random random{5};
    OrgWorld world{random};

    // arena width and height
    const int num_h_boxes = 50;
    const int num_w_boxes = 50;
    const double RECT_SIDE = 10;
    const double width{num_w_boxes * RECT_SIDE};
    const double height{num_h_boxes * RECT_SIDE};

    emp::web::Canvas canvas{width, height, "canvas"};

    public:

    SwarmAnimator() {
        // shove canvas into the div
        // along with a control button
        doc << canvas;
        doc << GetToggleButton("Toggle");
        doc << GetStepButton("Step");

        Organism* new_org = new Organism(&random);
        new_org->SetWorld(&world);
        world.Inject(*new_org);

        world.SetPopStruct_Grid(num_w_boxes, num_h_boxes);
        world.Resize(num_h_boxes,num_w_boxes);

    }

    void DoFrame() override {
        canvas.Clear();
        world.Update();

        int org_num = 0;
        for (int x = 0; x < num_w_boxes; x++){
            for (int y = 0; y < num_h_boxes; y++) {
                if (world.IsOccupied(org_num)) {
                    canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "black", "black");
                } else {
                    canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "white", "black");
                }
                
                if (world.SandParticleAt(org_num)) {
                    // Draw circles for sand particles
                    canvas.Circle(x * RECT_SIDE + RECT_SIDE / 2, y * RECT_SIDE + RECT_SIDE / 2, RECT_SIDE / 4, "yellow", "black");
                }

                org_num++;
            }
        }

    }

};

SwarmAnimator animator;

int main() {animator.Step();}