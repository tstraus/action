#include <unordered_map>
#include <functional>
#include <utility>
#include <mutex>

namespace tstraus
{
    template<class Signature>
    class Action
    {
    public:
        // make the given function the only one in the action
        template<typename Function>
        void operator = (Function&& f)
        {
            std::lock_guard<std::mutex> lock(mtx);

            actions.clear();

            actions[0] = std::forward<Function>(f);
        }

        // adds a function to the action
        template<typename Function>
        uint32_t operator += (Function&& f)
        {
            std::lock_guard<std::mutex> lock(mtx);

            actions[++nextID] = std::forward<Function>(f);

            return nextID;
        }

        // remove the function with the given id from the action
        void operator -= (uint32_t id)
        {
            std::lock_guard<std::mutex> lock(mtx);

            actions.erase(id);
        }

        // execute the action
        template<class... Args>
        void operator () (Args&&... args)
        {
            std::lock_guard<std::mutex> lock(mtx);

            for(auto& f : actions)
                f.second(args...);
        }

        // clear the functions in the action
        void clear()
        {
            std::lock_guard<std::mutex> lock(mtx);

            nextID = 0;
            actions.clear();
        }

    private:
        uint32_t nextID;

        std::mutex mtx;

        std::unordered_map<uint32_t, std::function<Signature>> actions;
    };
}
