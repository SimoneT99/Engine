#include "./AbstractInputController.hpp"
#include <map>
#include <thread>
#include <atomic>

class InputController : public AbstractInputController{

    private:
        float polling_rate;
        int ticks_to_wait;

        //multithreading setup
        std::thread input_thread;
        std::atomic<bool> running;
    
        void inputLoop();

    public:
        InputController(
            float polling_rate,
            int ticks_to_wait
        )
        {};

        ~InputController();

};