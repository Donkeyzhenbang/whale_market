#include <iostream>
#include <vector>
#include <string>
#include <functional>
//基类
class Menu{
public:
    std::string title;
    std::vector<Menu*> sub_menu;
    Menu(const std::string& t) : title(t) {}
    void add_sub_menu(Menu* menu) { sub_menu.push_back(menu); }
    void display(){
        std::cout << std::endl << "----- " << title <<  " -----" << std::endl;
        for(size_t i = 0; i < sub_menu.size(); i ++){
            std::cout << i + 1 << sub_menu[i]->title << std::endl;
        }
        std::cout << "0.返回" << std::endl << "请输入选项: ";
    }
    virtual void handle_input() = 0;//pure virtual 子类实现
};

//普通菜单
class SimpleMenu : public Menu{
public:
    SimpleMenu(const std::string& t) : Menu(t) {}
    void handle_input(){
        int choice;
        display();
        do{
            std::cin >> choice;
            if(choice > 0 && choice <= static_cast<int>(sub_menu.size())){
                sub_menu[choice - 1]->handle_input();
                display();
            }
        } while (choice != 0);
    }
};

//执行登陆函数切换普通菜单
class LoginMenu : public Menu{
public:
    std::function<bool()> bool_callback;
    LoginMenu(const std::string& t, std::function<bool()> cb = nullptr) : Menu(t), bool_callback(cb) {} 

    void handle_input(){
        if(bool_callback){
            bool res = bool_callback();
            if(res)
                sub_menu[0]->handle_input();// SimpleMenu::handle_input();
        }
    }
};

//执行功能性函数
class FuncMenu : public Menu{
public:
    std::function<void()> void_callback; //!修正callback声明 需要的是一个std::function对象 而不是一个函数不要加()
    FuncMenu(const std::string& t, std::function<void()> cb = nullptr) : Menu(t), void_callback(cb) {} 
    void handle_input(){
        if(void_callback)
            void_callback();
        else    
            std::cout << std::endl << "还未设置回调函数"  << std::endl << std::endl;
    }
};

bool user_login_callback();
bool admin_login_callback();
void self_info_callback();

//主菜单
SimpleMenu main_menu("主菜单");

//主菜单->用户/注册/管理员
LoginMenu user_login_menu("用户登录", &user_login_callback);
LoginMenu admin_login_menu("管理员登录", &admin_login_callback);
FuncMenu user_signup_menu("用户注册");

//Login函数绑定->用户/管理员
SimpleMenu user_menu("用户菜单");
SimpleMenu admin_menu("管理员菜单");

//用户->个人信息/买家/卖家
SimpleMenu buyer_menu("买家菜单");
SimpleMenu seller_menu("卖家菜单");
SimpleMenu info_menu("个人信息");

//买家-> 查看/购买
FuncMenu view_good_menu("查看商品");
FuncMenu buy_good_menu("购买商品");

//卖家->出售/我的商品/修改信息
FuncMenu sell_good_menu("出售商品");
FuncMenu self_good_menu("我的商品");
SimpleMenu modify_good_menu("修改商品信息");
FuncMenu order_good_menu("交易订单");

//个人信息->我的信息/修改/充值
SimpleMenu modify_info_menu("修改个人信息");
FuncMenu self_info_menu("我的信息", &self_info_callback);
FuncMenu recharge_info_menu("个人充值");


 //后续重写为数据库/读文件
bool user_login_callback() 
{
    std::string username, password;
    std::cout << "username :" ;
    std::cin >> username;
    std::cout << "password :" ;
    std::cin >> password;
    if(username == "123" && password == "123")
        return true;
    else    
        return false;
}

//后续重写为数据库/读文件
bool admin_login_callback() 
{ 
    std::string username, password;
    std::cout << "username :" ;
    std::cin >> username;
    std::cout << "password :" ;
    std::cin >> password;
    if(username == "admin" && password == "passwd")
        return true;
    else    
        return false;
}

void self_info_callback()
{
    std::cout << std::endl <<  "----- " << self_info_menu.title <<  " -----" << std::endl;
    std::cout << "ID        | 0000" << std::endl;
    std::cout << "UserName  | 0000" << std::endl;
    std::cout << "Money     | 0000" << std::endl;
}


void workflow()
{
    main_menu.add_sub_menu(&user_login_menu);
    main_menu.add_sub_menu(&admin_login_menu);
    main_menu.add_sub_menu(&user_signup_menu);

    user_login_menu.add_sub_menu(&user_menu);
    admin_login_menu.add_sub_menu(&admin_menu);

    user_menu.add_sub_menu(&buyer_menu);
    user_menu.add_sub_menu(&seller_menu);
    user_menu.add_sub_menu(&info_menu);

    buyer_menu.add_sub_menu(&view_good_menu);
    buyer_menu.add_sub_menu(&buy_good_menu);
    
    seller_menu.add_sub_menu(&sell_good_menu);
    seller_menu.add_sub_menu(&self_good_menu);
    seller_menu.add_sub_menu(&modify_good_menu);
    seller_menu.add_sub_menu(&order_good_menu);

    info_menu.add_sub_menu(&self_info_menu);
    info_menu.add_sub_menu(&modify_info_menu);
    info_menu.add_sub_menu(&recharge_info_menu);
    
    main_menu.handle_input();
}

int main()
{
    workflow();
    return 0;
}