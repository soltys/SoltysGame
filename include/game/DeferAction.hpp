#include <functional>
class DeferAction
{
public:
    DeferAction(std::function<void()> func) : m_func(func)
    {
    }
    ~DeferAction()
    {
        m_func();
    }

private:
    std::function<void()> m_func;
};