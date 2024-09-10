#include <iostream>
#include <string>
#include <vector>


// 预声明类
class UserMenu;
class AdminMenu;
class BuyerMenu;
class SellerMenu;
//如果没有登陆函数 可以设置单个类 纯粹分级写一个add_sub_menu往里面添加即可
class Menu
{
public:
    std::string title;
    Menu(const std::string &t) : title(t) {}
    virtual void display()
    {
        std::cout << "----- " << title << " -----" << std::endl;
    }
    virtual void handle_input() {}
};

//virtual 关键字表示这个函数在基类中是虚拟的，这意味着函数可以在派生类中被重写。
//= 0 是一个特殊的语法，表示这个函数在基类中没有定义，它是一个接口，必须在派生类中实现。
class LoginMenu : public Menu
{
public:
    LoginMenu(const std::string& t) : Menu(t) {}
    virtual bool login() = 0;

};

class UserLoginMenu : public LoginMenu
{
public:
    UserLoginMenu() : LoginMenu ("用户登录") {}
    bool login() override {
        std::string username, password;
        std::cout << "username: " ;
        std::cin >> username;
        std::cout << "psaaword: ";
        std::cin >> password;
        if(username == "123" && password == "123"){ // 模拟登录成功
            std::cout << "用户登录成功" << std::endl;
            return true; 
        }
        std::cout << "用户登录失败，请重试" << std::endl;
        return false;
    }

    void handle_input() override;
};

class AdminLoginMenu : public LoginMenu
{
public:
    AdminLoginMenu() : LoginMenu ("用户登录") {}
    bool login() override {
        std::string username, password;
        std::cout << "username: " ;
        std::cin >> username;
        std::cout << "psaaword: ";
        std::cin >> password;
        if(username == "admin" && password == "passwd"){ // 模拟登录成功
            std::cout << "管理员登录成功" << std::endl;
            return true; 
        }
        std::cout << "管理员登录失败，请重试" << std::endl;
        return false;
    }

    void handle_input() override;
};


class UserMenu : public Menu
{
public:
    UserMenu() : Menu("用户菜单") {}
    void handle_input() override;
};

class AdminMenu : public Menu
{
public:
    AdminMenu() : Menu("管理员菜单") {}
    void handle_input() override;
};
class BuyerMenu : public Menu
{
public:
    BuyerMenu() : Menu("买家菜单") {}
    void handle_input() override {
        int choice;
        do {
            display();
            std::cout << "1. 查看商品\n2. 购买商品\n0. 返回\n请输入选项: ";
            std::cin >> choice;
            if (choice == 1) {
                std::cout << "查看商品" << std::endl;
                // 添加查看商品逻辑
            } else if (choice == 2) {
                std::cout << "购买商品" << std::endl;
                // 添加购买商品逻辑
            }
        } while (choice != 0);
    }
};
class SellerMenu : public Menu
{
public:
    SellerMenu() : Menu("卖家菜单") {}
    void handle_input() override {
        int choice;
        do {
            display();
            std::cout << "1. 出售商品\n2. 我的商品\n0. 返回\n请输入选项: ";
            std::cin >> choice;
            if (choice == 1) {
                std::cout << "出售商品" << std::endl;
                // 添加出售商品逻辑
            } else if (choice == 2) {
                std::cout << "我的商品" << std::endl;
                // 添加我的商品逻辑
            }
        } while (choice != 0);
    }
};

//!默认private 记得写public
class MainMenu : public Menu
{
public:
    MainMenu() : Menu("主菜单") {}
    void handle_input() override
    {
        int choice;
        do {
            display();
            std::cout << "1. 用户登录\n2. 管理员登录\n0. 返回\n请输入选项: ";
            std::cin >> choice;
            if (choice == 1) {
                UserLoginMenu user_login_menu;
                user_login_menu.handle_input();
                // 添加出售商品逻辑
            } else if (choice == 2) {
                AdminLoginMenu admin_login_menu;
                admin_login_menu.handle_input();
                // 添加我的商品逻辑
            }
        } while (choice != 0);
    }
};

void UserLoginMenu::handle_input()
{
    if(login()){
        UserMenu user_menu;
        user_menu.handle_input();
    }
}

void UserMenu::handle_input()
{
    int choice;
    do{
        display();
        std::cout << "1. 买家菜单\n2. 卖家菜单\n0. 返回\n请输入选项: " ;
        std::cin >> choice;
        if(choice == 1){
            BuyerMenu buyer_menu;
            buyer_menu.handle_input();
        }
        else if(choice == 2){
            SellerMenu seller_menu;
            seller_menu.handle_input();
        }

    }while(choice != 0);
}
void AdminLoginMenu::handle_input()
{
    if(login()){
        AdminMenu admin_menu;
        admin_menu.handle_input();
    }
}

void AdminMenu::handle_input()
{
    int choice;
        do{
        display();
        std::cout << "1. 查看所有商品\n2. 删除用户\n0. 返回\n请输入选项: " ;
        std::cin >> choice;
        if (choice == 1) {
            std::cout << "查看所有商品" << std::endl;
            // 添加查看商品逻辑
        } else if (choice == 2) {
            std::cout << "删除用户" << std::endl;
            // 添加删除用户逻辑
        }

    }while(choice != 0);
}

int main()
{

    MainMenu main_menu;
    // 处理输入
    main_menu.handle_input();
    return 0;
}