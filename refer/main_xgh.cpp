#include <string>
#include <iostream>

class ChangeMenuBase {
public:
    virtual void back();
    virtual void open();
};

class UserMenuBase {
public:
    virtual void open();
    virtual void back();
    virtual void change_info();
};

class ChangableMenu : public UserMenuBase {
public:
    ChangeMenuBase *change_base;
};

class ChangeGoodMenu : public ChangeMenuBase {

};

class ChangePersonMenu : public ChangeMenuBase {

};

class PersonMenu : public ChangableMenu {
public:
    PersonMenu() 
    {
        change_base = new ChangePersonMenu();
    }
    void my_info();
    void recharge();
    void change_info() override 
    {

    }
    void back() override
    {

    }
};

class SellerMenu : public ChangableMenu {
public:
    SellerMenu()
    {
        change_base = new ChangeGoodMenu();
    }
    void sell();
    void my_good();
    void delete_good();
    void query_ticket();

    void change_info() override 
    {

    }
    void back() override
    {

    }
};

class BuyerMenu : public UserMenuBase {
public:
    void query_good();
    void buy_good();
    void search_good();
    void query_ticket();
    void query_good_info();
    void back() override 
    {

    }
};

class ManagerMenu : public UserMenuBase {
public:
    void get_all_good();
    void search_good();
    void query_good();
    void get_all_user();
    void delete_user();
    void delete_good();
    void back() override
    {
        
    }
};

class SuperMenu : public UserMenuBase {
public:
    void back() override 
    {

    }
};

class MenuFactory {
public:
    UserMenuBase* get_menu(const std::string& loginer) 
    {
        // 少打几个字
        const std::string& lg = loginer;
        if(lg == "manager") return new ManagerMenu();
        if(lg == "buyer")   return new BuyerMenu();
        if(lg == "seller")  return new SellerMenu();
        if(lg == "person")  return new PersonMenu();
        if(lg == "super")   return new SuperMenu();
    }
};

class ChangeMenuFactory {
public:
    ChangableMenu* get_menu(const std::string& menu_name) 
    {
        // 少打几个字
        const std::string& mn = menu_name;
        if (mn == "person") return new PersonMenu();
        if (mn == "seller") return new SellerMenu();
    }
};


int main()
{
    UserMenuBase* menu;
    std::string loginer;
    std::cin >> loginer;
    menu = MenuFactory{}.get_menu(loginer);
    menu->open(); // 当他没有
    

    // 有个要修改信息的需求
    ChangableMenu* c_menu;
    std::string menu_name;
    c_menu = ChangeMenuFactory{}.get_menu(menu_name);
    if (1) // 不知名的地方获取的
    {
        c_menu->change_base->open();
    }
    
    return 0;
}
