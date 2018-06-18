#include <unordered_map>
#include <functional>
#include <utility>

namespace tstraus
{
    template<class Signature>
    class Action
    {
    public:
        // adds a function to the action
        template<typename Functor>
        uint32_t operator += (Functor&& f)
        {
            actions[nextID] = std::forward<Functor>(f);

            return nextID++;
        }

        // remove the function with the given id from the action
        void operator -= (uint32_t id)
        {
            actions.erase(id);
        }

        // execute the action
        template<class... Args>
        void operator () (Args&&... args) const
        {
            for(auto& f : actions)
                f.second(args...);
        }

    private:
        uint32_t nextID;

        std::unordered_map<uint32_t, std::function<Signature>> actions;
    };
}
