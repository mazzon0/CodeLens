#ifndef UI_H
#define UI_H

class UI {
public:
    static void Init() { Get().iInit(); }
    static void Destroy() { Get().iDestroy(); }

private:
    static UI& Get() {
        static UI instance;
        return instance;
    }

    void iInit();
    void iDestroy();
};

#endif
