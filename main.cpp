#include <bits/stdc++.h>
#include <chrono>
using namespace std;

vector<vector<string>> customer_db;
vector<vector<string>> employee_db;
vector<vector<string>> car_db;
vector<vector<string>> manager_set;
vector<string> wb_row;

int rent = 100;
int max_days = 15;
int max_dues = 4000;
int min_rec = 70;
int def_rec = 100;
int max_cars = 5;
int fine = 200;
int daytime = 60;
string manager_id = "CarSysMan", manager_pw = "MngPass";
void readfile1(string fname)
{
    vector<string> row;
    string line, word;

    fstream file(fname, ios::in);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            row.clear();
            stringstream str(line);
            while (getline(str, word, ','))
                row.push_back(word);
            customer_db.push_back(row);
        }
    }
    else
        cout << "Could not open the file\n";
}
void readfile2(string fname)
{
    vector<string> row;
    string line, word;

    fstream file(fname, ios::in);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            row.clear();
            stringstream str(line);
            while (getline(str, word, ','))
                row.push_back(word);
            employee_db.push_back(row);
        }
    }
    else
        cout << "Could not open the file\n";
}
void readfile3(string fname)
{
    vector<string> row;
    string line, word;

    fstream file(fname, ios::in);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            row.clear();
            stringstream str(line);
            while (getline(str, word, ','))
                row.push_back(word);
            car_db.push_back(row);
        }
    }
    else
        cout << "Could not open the file\n";
}
void readfile4(string fname)
{
    vector<string> row;
    string line, word;
    manager_set.clear();
    fstream file(fname, ios::in);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            row.clear();
            stringstream str(line);
            while (getline(str, word, ','))
                row.push_back(word);
            manager_set.push_back(row);
        }
        rent = stoi(manager_set[0][0]);
        max_days = stoi(manager_set[0][1]);
        max_dues = stoi(manager_set[0][2]);
        min_rec = stoi(manager_set[0][3]);
        def_rec = stoi(manager_set[0][4]);
        max_cars = stoi(manager_set[0][5]);
        fine = stoi(manager_set[0][6]);
        daytime = stoi(manager_set[0][7]);
    }
    else
        cout << "Could not open the file\n";
}
void writefile(vector<vector<string>> par, string fname)
{
    fstream fout(fname, ios::out);
    fout.clear();
    for (auto x : par)
    {
        for (auto y : x)
        {
            fout << y;
            if (y != x.back())
                fout << ",";
        }
        fout << "\n";
    }
}
class User
{

public:
    int user_type;
    string name;
    string id;
    int cars;
    int user_rec;
    int due;
    virtual void display() = 0;
    void see_available_cars();
    void see_my_cars();
    void rent_car();
    void check_available();
    void clear_due();
};

void User::see_available_cars()
{
    cout << "Car Model : Car ID\n";
    for (auto it : car_db)
    {
        if (it[2] == "not_rented")
        {
            cout << it[0] << " : " << it[1] << "\n";
        }
    }
}
void User::see_my_cars()
{
    cout << "Car Model : Car ID : Days till due date\n";
    for (auto it : car_db)
    {
        if (it[3] == this->id && it[2] == "rented")
        {
            string duedate;
            if ((time(0) - stoll(it[4])) / daytime > max_days)
            {
                duedate = "Overdue";
            }
            else
            {
                duedate = to_string(max_days - ((time(0) - stoll(it[4])) / daytime));
            }
            cout << it[0] << " : " << it[1] << " : " << duedate << "\n";
        }
    }
}
void User::rent_car()
{
    if (this->due < max_dues && this->cars < (int)((float)max_cars * ((float)this->user_rec / (float)def_rec)) && this->user_rec >= min_rec)
    {
        string id;

        cout << "Enter ID of Car : ";
        cin >> id;
        int f = 0;
        for (auto it=car_db.begin();it!=car_db.end();it++)
        {
            f=1;
            if ((*it)[1] == id)
            {
                f=1;
                if((*it)[2]=="not_rented"){
                    wb_row.clear();wb_row.push_back((*it)[0]);wb_row.push_back((*it)[1]);wb_row.push_back("rented");wb_row.push_back(this->id);wb_row.push_back(to_string(time(0)));
                    car_db.erase(it);
                    car_db.push_back(wb_row);
                    this->cars++;
                cout<<"Car rented successfully\n";break;
                }
                else {cout<<"Car already rented\n";}
                }
                
            
        }
        if (!f)
        {
            cout << "Invalid Car ID\n";
        }
    }
    else if (this->cars < (int)((float)max_cars * ((float)this->user_rec / (float)def_rec)) && this->user_rec >= min_rec)
    {
        cout << "Your high pending dues make you ineligible to rent more cars\n";
    }
    else if (this->user_rec >= min_rec)
    {
        cout << "You have reached your limit for renting cars\n";
    }
    else
    {
        cout << "Your previous record with the company makes you ineligible to rent cars\n";
    }
}

void User::check_available()
{
    string id;
    cout << "Enter ID of the car : ";
    cin >> id;
    int f = 0;
    for (auto it : car_db)
    {
        if (it[1] == id)
        {
            f = 1;
            if (it[2] == "not_rented")
            {
                cout << "Car is available\n";
            }
            else
            {
                cout << "Car is not available\n";
            }
        }
    }
    if (!f)
    {
        cout << "Invalid Car ID\n";
    }
}
void User::clear_due()
{
    cout << "Your total accumulated due is : " << this->due << "\n";
    this->due = 0;
    cout << "This does not include rent of currently rented cars.\nYour dues are cleared.Thank you for using our Car Rental System!!\n";
}

class Customer : public User
{
private:
    string password;

public:
    int user_type = 1;
    void display();
    void return_car();
    Customer(string name, string id, int cust_rec, int cars, int due, string pw)
    {
        this->name = name;
        this->id = id;
        this->user_rec = cust_rec;
        this->cars = cars;
        this->due = due;
        this->password = pw;
    }
    ~Customer() {
        for(auto &it:customer_db){
            if(it[1]==this->id){
                it[2]=to_string(this->user_rec);it[3]=to_string(this->cars);it[4]=to_string(this->due);
            break;
            }
        }
    }
};

void Customer::display()
{
    int a;


    cout << "-------------------------------------------------------\n";
    cout << "1. Press 1 to display Profile\n";
    cout << "2. Press 2 to see available cars\n";
    cout << "3. Press 3 to see rented cars\n";
    cout << "4. Press 4 to see availability of a specific car\n";
    cout << "5. Press 5 to rent a car\n";
    cout << "6. Press 6 to return a car\n";
    cout << "7. Press 7 to clear dues\n";
    cout << "8. Press 8 to exit\n";
    cout << "-------------------------------------------------------\n";
    cin >> a;
    switch (a)
    {
    case 1:
        cout << "Customer Profile : \n";
        cout << "Name:" << this->name << "  "
             << "ID:" << this->id << "  "
             << "Customer Record:" << this->user_rec << "  "
             << "No. of cars rented:" << this->cars << "  "
             << "Due:" << this->due << "\n";
        this->display();
        break;
    case 2:
        this->see_available_cars();
        this->display();
        break;
    case 3:
        this->see_my_cars();
        this->display();
        break;
    case 4:
        this->check_available();
        this->display();
        break;
    case 5:
        this->rent_car();
        this->display();
        break;
    case 6:
        this->return_car();
        this->display();
        break;
    case 7:
        this->clear_due();
        this->display();
        break;
    case 8:
        cout << "Thank You\n";
        break;
    default:
        cout<<"Invalid Input\n";
    }
}

void Customer::return_car()
{
    string id;
    int cond = 7, input;
    

    cout << "Enter ID of Car : ";
    cin >> id;
    cout << "Enter the condition of the car(0(worst)-10(perfect condition))\n";
    cin >> input;
    if (input >= 0 && input <= 10)
    {
        cond = input;
    }
    int f = 0;
    for (auto &it : car_db)
    {
        if (it[1] == id)
        {
            f = 1;
            if (it[2] == "rented" && it[3] == this->id)
            {

                it[2] = "not_rented";
                int accdue = 0;
                int accfine = 0;
                this->user_rec -= 2 * (9 - cond);
                if (max_days < (time(0) - stoll(it[4])) / daytime)
                {
                    accdue = max_days * rent;
                    accfine = (((time(0) - stoll(it[4])) / daytime) - max_days) * fine;
                    this->user_rec -= (((time(0) - stoll(it[4])) / daytime) - max_days);
                }
                else
                {
                    accdue = ((time(0) - stoll(it[4])) / daytime) * rent;
                }
                cout << "Rent to be paid for the car is : " << accdue << "\n";
                cout << "Fine to be paid is : " << accfine << "\n";
                this->due += accdue + accfine;
                cout << "Car has been returned\n";
                this->cars--;
                break;
            }
            else
            {
                cout << "Car has not been rented by you\n";
                break;
            }
        }
    }
    if (!f)
    {
        cout << "Invalid Car ID\n";
    }
}

class Employee : public User
{
private:
    string password;

public:
    int user_type = 2;
    void display();
    void return_car();
    Employee(string name, string id, int emp_rec, int cars, int due, string pw)
    {
        this->name = name;
        this->id = id;
        this->user_rec = emp_rec;
        this->cars = cars;
        this->due = due;
        this->password = pw;
    }
    ~Employee() {
        for(auto &it:employee_db){
            if(it[1]==this->id){
                it[2]=to_string(this->user_rec);it[3]=to_string(this->cars);it[4]=to_string(this->due);
            break;
            }
        }
    }
};

void Employee::display()
{
    int a;


    cout << "-------------------------------------------------------\n";
    cout << "1. Press 1 to display Profile\n";
    cout << "2. Press 2 to see available cars\n";
    cout << "3. Press 3 to see rented cars\n";
    cout << "4. Press 4 to see availability of a specific car\n";
    cout << "5. Press 5 to rent a car\n";
    cout << "6. Press 6 to return a car\n";
    cout << "7. Press 7 to clear dues\n";
    cout << "8. Press 8 to exit\n";
    cout << "-------------------------------------------------------\n";
    cin >> a;
    switch (a)
    {
    case 1:
        cout << "Employee Profile : \n";
        cout << "Name:" << this->name << "  "
             << "ID:" << this->id << "  "
             << "Employee Record:" << this->user_rec << "  "
             << "No. of cars rented:" << this->cars << "  "
             << "Due:" << this->due << "\n";
        this->display();
        break;
    case 2:
        this->see_available_cars();
        this->display();
        break;
    case 3:
        this->see_my_cars();
        this->display();
        break;
    case 4:
        this->check_available();
        this->display();
        break;
    case 5:
        this->rent_car();
        this->display();
        break;
    case 6:
        this->return_car();
        this->display();
        break;
    case 7:
        this->clear_due();
        this->display();
        break;
    case 8:
        cout << "Thank You\n";
        break;
    default:
        cout<<"Invalid Input\n";
    }
}

void Employee::return_car()
{
    string id;
    int cond = 7, input;
    float frac=0.85;


    cout << "Enter ID of Car : ";
    cin >> id;
    cout << "Enter the condition of the car(0(worst)-10(perfect condition))\n";
    cin >> input;
    if (input >= 0 && input <= 10)
    {
        cond = input;
    }
    int f = 0;
    for (auto &it : car_db)
    {
        if (it[1] == id)
        {
            f = 1;
            if (it[2] == "rented" && it[3] == this->id)
            {

                it[2] = "not_rented";
                int accdue = 0;
                int accfine = 0;
                this->user_rec -= 2 * (9 - cond);
                if (max_days < (time(0) - stoll(it[4])) / daytime)
                {
                    accdue = max_days * ((int)((float)rent * frac));
                    accfine = (((time(0) - stoll(it[4])) / daytime) - max_days) * fine;
                    this->user_rec -= (((time(0) - stoll(it[4])) / daytime) - max_days);
                }
                else
                {
                    accdue = ((time(0) - stoll(it[4])) / daytime) * ((int)((float)rent * frac));
                }
                cout << "Rent to be paid for the car is : " << accdue << "\n";
                cout << "Fine to be paid is : " << accfine << "\n";
                this->due += accdue + accfine;
                cout << "Car has been returned\n";
                this->cars--;
                break;
            }
            else
            {
                cout << "Car has not been rented by you\n";
                break;
            }
        }
    }
    if (!f)
    {
        cout << "Invalid Car ID\n";
    }
}

class Manager : public User
{
private:
    string password;

public:
    int user_type = 3;
    void display();
    void see_all_cars();
    void see_all_customers();
    void see_all_employees();
    void change_settings();
    void add_customer();
    void upd_customer();
    void rm_customer();
    void add_employee();
    void upd_employee();
    void rm_employee();
    void add_car();
    void upd_car();
    void rm_car();
    void default_set();
};

void Manager::display()
{
    int a;


    cout << "-------------------------------------------------------\n";
    cout << "                    Manager's Menu                     \n";
    cout << "1. Press 1 to change System settings(rent,fine..etc)\n";
    cout << "2. Press 2 to see data of all cars\n";
    cout << "3. Press 3 to see data of all customers\n";
    cout << "4. Press 4 to see data of all employees\n";
    cout << "5. Press 5 to modify the car database\n";
    cout << "6. Press 6 to modify the customer database\n";
    cout << "7. Press 7 to modify the employee database\n";
    cout << "8. Press 8 to exit\n";
    cout << "9. Press 9 to reset system settings\n";
    cout << "-------------------------------------------------------\n";
    cin >> a;
    int b;
    switch (a)
    {
    case 1:
        this->change_settings();
        this->display();
        break;
    case 2:
        this->see_all_cars();
        this->display();
        break;
    case 3:
        this->see_all_customers();
        this->display();
        break;
    case 4:
        this->see_all_employees();
        this->display();
        break;
    case 5:
        cout << "1. Press 1 to add Car\n";
        cout << "2. Press 2 to update Car\n";
        cout << "3. Press 3 to remove Car\n";
        cin >> b;
        switch (b)
        {
        case 1:
            this->add_car();
            break;
        case 2:
            this->upd_car();
            break;
        case 3:
            this->rm_car();
            break;
        }
        this->display();
        break;
    case 6:
        cout << "1. Press 1 to add Customer\n";
        cout << "2. Press 2 to update Customer\n";
        cout << "3. Press 3 to remove Customer\n";
        cin >> b;
        switch (b)
        {
        case 1:
            this->add_customer();
            break;
        case 2:
            this->upd_customer();
            break;
        case 3:
            this->rm_customer();
            break;
        }
        this->display();
        break;
    case 7:
        cout << "1. Press 1 to add Employee\n";
        cout << "2. Press 2 to update Employee\n";
        cout << "3. Press 3 to remove Employee\n";
        cin >> b;
        switch (b)
        {
        case 1:
            this->add_employee();
            break;
        case 2:
            this->upd_employee();
            break;
        case 3:
            this->rm_employee();
            break;
        }
        this->display();
        break;
    case 8:
        cout << "Thank You\n";
        break;
    case 9:
        this->default_set();
        this->display();
        break;
    default:
        cout<<"Invalid Input\n";break;
    }
}

void Manager::change_settings()
{
    wb_row.clear();
    vector<vector<string>> temp;
    int tem;
    cout << "Set rent per day : ";
    cin >> tem;
    wb_row.push_back(to_string(tem));
    cout << "Set maximum rent duration(in days) : ";
    cin >> tem;
    wb_row.push_back(to_string(tem));
    cout << "Set maximum allowed due : ";
    cin >> tem;
    wb_row.push_back(to_string(tem));
    cout << "Set minimum allowed customer/employee record : ";
    cin >> tem;
    wb_row.push_back(to_string(tem));
    cout << "Set default customer/employee record : ";
    cin >> tem;
    wb_row.push_back(to_string(tem));
    cout << "Set maximum cars allowed to be rented per person : ";
    cin >> tem;
    wb_row.push_back(to_string(tem));
    cout << "Set fine per day : ";
    cin >> tem;
    wb_row.push_back(to_string(tem));
    cout << "Set duration of a day(in seconds) for ease of simulation : ";
    cin >> tem;
    wb_row.push_back(to_string(tem));
    temp.push_back(wb_row);
    writefile(temp, "managersettings.csv");
    readfile4("managersettings.csv");
}

void Manager::see_all_cars()
{
    cout << "Car Model : Car ID : Renter : Days till due date\n";
    for (auto it : car_db)
    {
        cout << it[0] << " : " << it[1] << " : ";
        if (it[2] == "rented")
        {
            cout << it[3] << " : ";
            if ((time(0) - stoll(it[4])) / daytime > max_days)
            {
                cout << "Overdue\n";
            }
            else
            {
                cout << to_string(max_days - ((time(0) - stoll(it[4])) / daytime)) << "\n";
            }
        }
        else
        {
            cout << "Not Rented\n";
        }
    }
    cout << "Total Cars : " << car_db.size() << "\n";
}

void Manager::see_all_customers()
{
    cout << "Customer Name : Customer ID : Customer Record : Cars Rented : Pending Due\n";
    for (auto it : customer_db)
    {
        cout << it[0] << " : " << it[1] << " : " << it[2] << " : " << it[3] << " : " << it[4] << "\n";
    }
    cout << "Total Customers : " << customer_db.size() << "\n";
}

void Manager::see_all_employees()
{
    cout << "Employee Name : Employee ID : Employee Record : Cars Rented : Pending Due\n";
    for (auto it : employee_db)
    {
        cout << it[0] << " : " << it[1] << " : " << it[2] << " : " << it[3] << " : " << it[4] << "\n";
    }
    cout << "Total Employees : " << employee_db.size() << "\n";
}

void Manager::add_customer()
{
    wb_row.clear();
    string n, id;
    cout << "Enter Customer Name : ";
    cin >> n;
    wb_row.push_back(n);
B:
    cout << "Enter Customer ID : ";
    cin >> id;
    for (auto it : customer_db)
    {
        if (it[1] == id)
        {
            cout << "ID already taken.\n";
            goto B;
        }
    }
    wb_row.push_back(id);
    wb_row.push_back(to_string(def_rec));
    wb_row.push_back(to_string(0));
    wb_row.push_back(to_string(0));
    wb_row.push_back(n + '@' + id);
    customer_db.push_back(wb_row);
}

void Manager::upd_customer()
{
    string id;wb_row.clear();string temp;
    cout<<"Enter ID of Customer : ";cin>>id;
    auto it=customer_db.begin();
    for(;it!=customer_db.end();it++){
        if((*it)[1]==id){break;}
    }
    if(it==customer_db.end()){cout<<"Invalid Customer ID\n";}
    else {
        cout<<"Enter new Name : ";cin>>temp;wb_row.push_back(temp);
        cout<<"Enter new Password : ";cin>>temp;wb_row.push_back((*it)[1]);
        wb_row.push_back((*it)[2]);wb_row.push_back((*it)[3]);wb_row.push_back((*it)[4]);wb_row.push_back(temp);
    customer_db.erase(it);customer_db.push_back(wb_row);
    }
}

void Manager::rm_customer()
{
    cout << "Enter Customer ID : ";
    cin >> id;int f=0;
    for (auto it = customer_db.begin(); it != customer_db.end(); it++)
    {f=1;
        if ((*it)[1] == id && stoi((*it)[3]) == 0)
        {
            cout<<"The due to be paid by the Customer is : "<<stoi((*it)[4])<<"\n";
            customer_db.erase(it);
            cout << "Customer Deleted\n";
            break;
        }
        else if((*it)[1] == id && stoi((*it)[3]) != 0){cout<<"Customer has rented cars, and cannot be deleted\n";}
    }
    if(!f){cout<<"Invalid Customer ID\n";}
}
void Manager::add_employee()
{
    wb_row.clear();
    string n, id;
    cout << "Enter Employee Name : ";
    cin >> n;
    wb_row.push_back(n);
C:
    cout << "Enter Employee ID : ";
    cin >> id;
    for (auto it : customer_db)
    {
        if (it[1] == id)
        {
            cout << "ID already taken.\n";
            goto C;
        }
    }
    wb_row.push_back(id);
    wb_row.push_back(to_string(def_rec));
    wb_row.push_back(to_string(0));
    wb_row.push_back(to_string(0));
    wb_row.push_back(n + '@' + id);
    employee_db.push_back(wb_row);
}

void Manager::upd_employee()
{
    string id;wb_row.clear();string temp;
    cout<<"Enter ID of Employee : ";cin>>id;
    auto it=employee_db.begin();
    for(;it!=employee_db.end();it++){
        if((*it)[1]==id){break;}
    }
    if(it==employee_db.end()){cout<<"Invalid Employee ID\n";}
    else {
        cout<<"Enter new Name : ";cin>>temp;wb_row.push_back(temp);
        cout<<"Enter new Password : ";cin>>temp;wb_row.push_back((*it)[1]);
        wb_row.push_back((*it)[2]);wb_row.push_back((*it)[3]);wb_row.push_back((*it)[4]);wb_row.push_back(temp);
    employee_db.erase(it);employee_db.push_back(wb_row);
    }
}

void Manager::rm_employee()
{
    cout << "Enter Employee ID : ";
    cin >> id;int f=0;
    for (auto it = employee_db.begin(); it != employee_db.end(); it++)
    {f=1;
        if ((*it)[1] == id &&stoi((*it)[3]) == 0)
        {
            cout<<"The due to be paid by the Employee is : "<<stoi((*it)[4])<<"\n";
            employee_db.erase(it);
            cout << "Employee Deleted\n";
            break;
        }
        else if((*it)[1] == id && stoi((*it)[3]) != 0){cout<<"Employee has rented cars, and cannot be deleted\n";}
    }
    if(!f){cout<<"Invalid Employee ID\n";}
}
void Manager::add_car()
{
    wb_row.clear();
    string n, id;
    cout << "Enter Car Model : ";
    cin >> n;
    wb_row.push_back(n);
D:
    cout << "Enter Car ID : ";
    cin >> id;
    for (auto it : car_db)
    {
        if (it[1] == id)
        {
            cout << "ID already taken.\n";
            goto D;
        }
    }
    wb_row.push_back(id);
    wb_row.push_back("not_rented");
    car_db.push_back(wb_row);
}

void Manager::upd_car()
{
    string id;wb_row.clear();string temp;
    cout<<"Enter ID of Car : ";cin>>id;
    auto it=car_db.begin();
    for(;it!=car_db.end();it++){
        if((*it)[1]==id){break;}
    }
    if(it==car_db.end()){cout<<"Invalid Car ID\n";}
    else {
        cout<<"Enter new Model : ";cin>>temp;wb_row.push_back(temp);wb_row.push_back((*it)[1]);
        cout<<"Enter new status(rented/not_rented) : ";cin>>temp;wb_row.push_back(temp);
        wb_row.push_back((*it)[3]);wb_row.push_back((*it)[4]);
    car_db.erase(it);car_db.push_back(wb_row);
    }
}

void Manager::rm_car()
{
    cout << "Enter Car ID : ";
    cin >> id;
    for (auto it = car_db.begin(); it != car_db.end(); it++)
    {
        if ((*it)[1] == id && (*it)[2]=="not_rented")
        {
            car_db.erase(it);
            cout << "Car Deleted\n";
            break;
        }
        else {cout<<"Car has been rented or the ID is invalid\n";}
    }
}

void Manager::default_set()
{
    wb_row.clear();
    rent = 100;
    wb_row.push_back(to_string(100));
    max_days = 15;
    wb_row.push_back(to_string(15));
    max_dues = 4000;
    wb_row.push_back(to_string(4000));
    min_rec = 70;
    wb_row.push_back(to_string(70));
    def_rec = 100;
    wb_row.push_back(to_string(100));
    max_cars = 5;
    wb_row.push_back(to_string(5));
    fine = 200;
    wb_row.push_back(to_string(200));
    daytime = 60;
    wb_row.push_back(to_string(60));
    vector<vector<string>> temp;
    temp.push_back(wb_row);
    writefile(temp, "managersettings.csv");
}

void display_menu()
{
    int a;


    cout << "---------------------------------------\n";
    cout << "\nWelcome to the Car Rental System!\n";
    cout << "1. Press 1 to log in as a Customer\n";
    cout << "2. Press 2 to log in as an Employee\n";
    cout << "3. Press 3 to log in as the Manager\n";
    cout << "4. Press 4 to exit\n";
    cout << "---------------------------------------\n";
    cin >> a;
    if (a == 1)
    {
        string id, pass;
        int f = 0;
        cout << "Enter Customer ID : ";
        cin >> id;
        cout << "Enter Your Password : ";
        cin >> pass;
        auto it = customer_db.begin();

        for (; it != customer_db.end(); it++)
        {
            if ((*it)[1] == id && (*it)[5] == pass)
            {
                Customer c((*it)[0], (*it)[1], stoi((*it)[2]), stoi((*it)[3]), stoi((*it)[4]), (*it)[5]);
                c.display();
            
                f = 1;
            }
            else if ((*it)[1] == id && (*it)[5] != pass)
            {
                cout << "Wrong Password\n";
                display_menu();
                f = 1;
            }
        }
        if (!f)
        {
            cout << "Invalid Customer ID\n";
            display_menu();
        }
    }
    else if (a == 2)
    {
        string id, pass;
        int f = 0;
        cout << "Enter Employee ID : ";
        cin >> id;
        cout << "Enter Your Password : ";
        cin >> pass;
        auto it = employee_db.begin();

        for (; it != employee_db.end(); it++)
        {
            if ((*it)[1] == id && (*it)[5] == pass)
            {
                Employee e((*it)[0], (*it)[1], stoi((*it)[2]), stoi((*it)[3]), stoi((*it)[4]), (*it)[5]);
                e.display();
                
                f = 1;
            }
            else if ((*it)[1] == id && (*it)[5] != pass)
            {
                cout << "Wrong Password\n";
                display_menu();
                f = 1;
            }
        }
        if (!f)
        {
            cout << "Invalid Employee ID\n";
            display_menu();
        }
    }
    else if (a == 3)
    {
        string id, pass;
        int f = 0;
        cout << "Enter Manager ID : ";
        cin >> id;
        cout << "Enter Your Password : ";
        cin >> pass;

        if (manager_id == id && manager_pw == pass)
        {
            Manager m;
            m.display();
            f = 1;
        }
        else if (manager_id == id && manager_pw != pass)
        {
            cout << "Wrong Password\n";
            display_menu();
            f = 1;
        }

        if (!f)
        {
            cout << "Invalid Manager ID\n";
            display_menu();
        }
    }
    else if (a == 4)
    {
        cout << "Thank You\n";
    }
    else
    {
        cout<<"Invalid input\n";
    }
}

int main()
{
    readfile1("customers.csv");
    readfile2("employees.csv");
    readfile3("cars.csv");
    readfile4("managersettings.csv");
    display_menu();
    writefile(customer_db, "customers.csv");
    writefile(employee_db, "employees.csv");
    writefile(car_db, "cars.csv");

    return 0;
}