# CS253: Car Rental System
This assignment is a Car Rental System coded in C++ using Object Oriented Programming. The code is present in [`main.cpp`](/main.cpp). There are 3 csv files for storing databases and a 4th one for saving system settings.
<br>The system allows three types of users- Customers, Employees and a Manager.<br>
[`customers.csv`](/customers.csv) and [`employees.csv`](/employees.csv) stores [name,id,user record,no. of cars,pending due,password]<br>
[`cars.csv`](/cars.csv) stores [model,id,status,renter,day rented]<br>
To run the program, type the following commands:
```
g++ main.cpp -o main.exe
.\main.exe
```
<br>
NOTE: There is a system Manager with login credentials id: CarSysMan , password: MngPass<br>
Only the manager can add or delete customers,employees and cars. When a customer/employee is added the default password is (name)@(id). This can be changed by update method.<br>
The manager has special privileges, such as:<br>
1) Changing system parameters(by pressing 1)<br>
2) Modifying databases to add/remove customers, employees, and cars<br>
3) Change passwords and names of customers and employees.<br>
