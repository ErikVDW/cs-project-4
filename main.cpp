/*
* ev176P4.cpp
*
* COSC 051 Fall 2015
* Project #4
*
* Due on: NOV 23, 2015
* Author: Erik Van de Water
*
*
* In accordance with the class policies and Georgetown's
* Honor Code, I certify that, with the exception of the
* class resources and those items noted below, I have neither
* given nor received any assistance on this project.
*
* References not otherwise commented within the program source code.
* Note that you should not mention any help from the TAs, the professor,
* or any code taken from the class textbooks.
*/

// -- PREPROCESSING --

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

// -- GLOBAL CONSTANTS

const string MESSAGE_GOODBYE = "Thank you for using the ASF System. ";
const string PROMPT_INPUT_FILE = "Please enter complete path and name of input data file: ";
const string MESSAGE_WELCOME = "Welcome to Appalachian Shape Fabricators.";
const string MESSAGE_INFO1 = "This app calculates surface area, volume, cost, \n";
const string MESSAGE_INFO2 = "and sales values based upon sales file data entries.";
const string LINE = "----------------------------------------------------------------------------------------";
const int SPACER = 10;


/************************************************************************
 ************************************************************************
 **                                                                    **
 **                    class Shape declaration                         **
 **                                                                    **
 **            This code is provided to students                       **
 **            in COSC 051 Fall 2015 to use in part                    **
 **            or in total for Project #4.                             **
 **            Students may use this code as their                     **
 **            own, without any attribution.                           **
 **                                                                    **
 ************************************************************************
 ************************************************************************/

class Shape {
private:
    // -- MEMBER VARIABLES --
    string region;
    char shapeCode;
    char materialCode;
    double radius;
    double height;
    string color;
    string customerNumber;

    //optional
    //you may add more data members but do not store calculated values
    //that would supercede the accessor functions below
    string shapeName;

public:
    // -- CONSTRUCTORS --

    Shape(); // default constructor
    Shape(string reg, char sc, char mc, double rad, double hei, string col, string custNum);

    // -- MUTATOR FUNCTIONS --

    void setRegion(string r) { region = r; }
    void setShapeCode(char sc) { shapeCode = sc; }
    void setMaterialCode( char mc ) { materialCode = mc; }
    void setRadius( double rad ) { radius = rad; }
    void setHeight( double hei ) { height = hei; }
    void setColor( string col ) { color = col; }
    void setCustomerNumber( string custNum ) { customerNumber = custNum; }

    // -- ACCESSORS --

    // --general accessors --
    string getRegion() const { return region; }
    char getShapeCode() const { return shapeCode; }
    char getMaterialCode() const { return materialCode; }
    double getRadius() const { return radius; }
    double getHeight() const { return height; }
    string getColor() const { return color; }
    string getCustomerNumber() const { return customerNumber; }

    // -- detailed calculations --
    double getManufacturingCost() const;
    double getSalesPrice() const;
    double getProfit() const;
    double getVolume() const;
    double getSurfaceArea() const;

    //optional
    //if you add any methods they should should go here
    string getShapeName() { return shapeName; }
    void setShapeName(string sN) { shapeName = sN; }


}; //END declaration class Shape



/************************************************************************
 ************************************************************************
 **                                                                    **
 **               Project #4 FUNCTION PROTOTYPES                       **
 **                                                                    **
 **            These prototypes are provided to students               **
 **            in COSC 051 Fall 2015 for Project #4.                   **
 **                                                                    **
 ************************************************************************
 ************************************************************************/

char displayMenu();

void uploadFile(string fName, bool &loadSuccess, vector<Shape> &vS);

void allDetails(const vector<Shape> &vS);

void customerDetails(const vector<Shape> &vS);

void summaryByShape(const vector<Shape> &vS);

void summaryByRegion(const vector<Shape> &vS);

int main(){
    // -- VARIABLES --

    // strings
    string fName =           "";

    // chars

    char choice;

    // bools

    bool loadSuccess = false;
    bool clearBool = false;

    // vectors
    vector<Shape> vectorShape;

    // -- OUTPUT GREETING --

    cout << "\n\n";
    cout << MESSAGE_WELCOME << endl;
    cout << MESSAGE_INFO1;
    cout << MESSAGE_INFO2;
    cout << "\n\n";

    // -- USER CHOICE OF OPTIONS --

    do {
        choice = displayMenu();
        if (choice == 'U' || choice == 'u') {
            cout << PROMPT_INPUT_FILE << endl;

            getline(cin, fName);

            uploadFile(fName, loadSuccess, vectorShape);
        }
        else if (choice == 'A' || choice == 'a') {
            if (loadSuccess == true) {
                allDetails(vectorShape);
            }
            else {
                cout << "\nPlease enter at least one data file before attempting " <<
                        "to display data\n" << endl;
                displayMenu();
            }
        }
        else if (choice == 'I' || choice == 'i') {
            if (loadSuccess == true) {
                customerDetails(vectorShape);
            }
            else {
                cout << "\nPlease enter at least one data file before attempting " <<
                        "to display data\n" << endl;
                displayMenu();
            }
        }
        else if (choice == 'R' || choice == 'r') {
            if (loadSuccess == true) {
                summaryByRegion(vectorShape);
            }
            else {
                cout << "\nPlease enter at least one data file before attempting " <<
                        "to display data\n" << endl;
                displayMenu();
            }
        }
        else if (choice == 'S' || choice == 's') {
            if (loadSuccess == true) {
                summaryByShape(vectorShape);
            }
            else {
                cout << "Please enter at least one data file before attempting" <<
                        "to display data" << endl;
                displayMenu();
            }
        }
        else if (choice == 'C' || choice == 'c') {
            vectorShape.clear();
            vectorShape.size() == 0 ? clearBool = true : clearBool = false;
            if (clearBool) {
                cout << "\nSuccessfully cleared data.\n" << endl;
                loadSuccess = false;
            }
        }
        else {
            if (choice != 'Q' && choice != 'q') {
                cout << "Invalid option.  Please try again.";
            }
        }
    } while (choice != 'Q' && choice != 'q');

//    Shape test;
//    Shape test2("Test2",'t','t',-10,-15,"Test2","Test2");
//
//    cout << test.getRegion() << test.getShapeCode() << test.getMaterialCode()
//    << test.getRadius() << test.getHeight() << test.getColor() << test.getCustomerNumber() << endl;
//    cout << test2.getRegion() << test2.getShapeCode() << test2.getMaterialCode()
//    << test2.getRadius() << test2.getHeight() << test2.getColor() << test2.getCustomerNumber() << endl;
    cout << MESSAGE_GOODBYE << endl;
    return 0;
}

// -- FUNCTION DEFINITIONS --

Shape::Shape() {
    setRegion("Test");
    setShapeCode('t');
    setMaterialCode('t');
    setRadius(-10);
    setHeight(-15);
    setColor("Test");
    setCustomerNumber("Test");
}

Shape::Shape(string reg,char sc, char mc, double rad, double hei, string col, string custNum) {
    setRegion(reg);
    setShapeCode(sc);
    setMaterialCode(mc);
    setRadius(rad);
    setHeight(hei);
    setColor(col);
    setCustomerNumber(custNum);

}
double Shape::getManufacturingCost() const {
    // -- VARIABLES --

    // doubles


    double materialCost =    0.0;
    double laborCost =       0.0;
    double cost =            0.0;

    //cost calculations

    if (this->getMaterialCode() == 'k' || this->getMaterialCode() == 'K') {
        materialCost = 1.26 * this->getSurfaceArea();
        laborCost = 256.27 + (0.4 * materialCost);
    }
    else if (this->getMaterialCode() == 'a' || this->getMaterialCode() == 'A') {
        materialCost = 0.49 * this->getSurfaceArea();
        laborCost = 32.10 + (0.1 * materialCost);
    }
    else {
        materialCost = 6.32 * this->getSurfaceArea();
        laborCost = 785.16 + (0.8 * materialCost);
    }

    // -- individual costs --

    // row output calculation variables

    cost = materialCost + laborCost;
    return cost;
}

double Shape::getSalesPrice() const{
    double cost = this->getManufacturingCost();
    double price = cost * 1.25;
    return price;
}
double Shape::getProfit() const{
    double price = this->getSalesPrice();
    double cost = this->getManufacturingCost();
    double profit = price - cost;
    return profit;
}
double Shape::getVolume() const{
    double volume = 0;
    if (this->getShapeCode() == 'o' || this->getShapeCode() == 'O') {
        volume  = (3.14*pow(this->getRadius(),2) * this->getHeight())/3;
    }
    else if (this->getShapeCode() == 'y' || this->getShapeCode() == 'Y'){
        volume = 3.14*pow(this->getRadius(),2)*this->getHeight();
    }
    else {
        volume = (4*3.14*pow(this->getRadius(),3))/3;
    }
    return volume;
}
double Shape::getSurfaceArea() const{
    double slantHeight =     0.0;
    double surfaceArea =     0.0;

    // return from other functions
    if (this->getShapeCode() == 'o' || this->getShapeCode() == 'O') {
        slantHeight = sqrt(pow(this->getRadius(),2)+pow(this->getHeight(),2));
        surfaceArea = 3.14*pow(this->getRadius(),2) + 3.14*this->getRadius()*slantHeight;
    }
    else if (this->getShapeCode() == 'y' || this->getShapeCode() == 'Y'){
        surfaceArea = 2*3.14*this->getRadius()*(this->getHeight() + this->getRadius());
    }
    else {
        surfaceArea = 4*3.14*pow(this->getRadius(),2);
    }

    return surfaceArea;
}
char displayMenu() {

    // -- CONSTANTS --

    const string UPLOAD = "Upload a regional sales data file";
    const string DETAILS = "Display details (all loaded data)";
    const string ID = "List sales for particular customer ID";
    const string REGION = "Display summary by region";
    const string SHAPE = "Display summary by shape code";
    const string CLEAR = "Clear all vectors";

    const int MENU = 45;
    const int CHAR = 6;

    // -- MENU OUTPUT --

    // option descriptions

    cout << setw(MENU) << UPLOAD;
    cout << setw(CHAR) << "U" << endl;
    cout << setw(MENU) << DETAILS;
    cout << setw(CHAR) << "A" << endl;
    cout << setw(MENU) << ID;
    cout << setw(CHAR) << "I" << endl;
    cout << setw(MENU) << REGION;
    cout << setw(CHAR) << "R" << endl;
    cout << setw(MENU) << SHAPE;
    cout << setw(CHAR) << "S" << endl;
    cout << setw(MENU) << CLEAR;
    cout << setw(CHAR) << "C" << endl;
    cout << setw(MENU) << "Quit";
    cout << setw(CHAR) << "Q" << endl;

    cout << "Please enter your choice: ";
    // -- CHOICE INPUT --
    char choice;
    cin >> choice;
    cin.ignore(500,'\n');
    return choice;
}
void uploadFile(string fName, bool &loadSuccess, vector<Shape> &vS) {

    const string MESSAGE_ERROR_FILE_OPEN = "The input file failed to open.";

    // -- VARIABLES --

    // -- numbers --

    // ints

    int fileYear =        0;
    int fileMonth =       0;
    int fileDay =         0;

    int orderYear =       0;
    int orderMonth =      0;
    int orderDay =        0;

    int currentRow =      0;
    int numErrors =       0;

    int numErrorsBefore = 0;

    int totalRecords =    0;
    int totalRecordsL =   0;
    int rowsCorrect =     0;
    int rowsIncorrect =   0;

    // doubles

    double radius =       0.0;
    double height =       0.0;

    // -- others --

    // strings

    string oneRow =          "";
    string headers =         "";
    string newLineAfterDate = "";

    string state =           "";
    string region =          "";
    string orderDate =       "";
    string color =           "";
    string customerNumber =  "";
    string firstName =       "";
    string lastName =        "";
    string address =         "";

    // chars

    char shapeCode =       'a';
    char materialCode =    'a';
    char dateDelimiter =    '/';

    // ifstream

    ifstream  inFileStream; //no initial value

    // -- INPUT FILE --

    inFileStream.open(fName.c_str());

    // -- TEST IF FILE IS VALID --

    if (!inFileStream) {
        cout << MESSAGE_ERROR_FILE_OPEN << endl;
        cout << "check to ensure the file: " << fName << " is valid.\n";
    }
    else {
        cout << fName << "successfully opened for reading.\n";

        // -- file date checking for line 1--

        inFileStream >> fileYear >> dateDelimiter >> fileMonth >> dateDelimiter >> fileDay;
        if (fileYear < 1000 || fileYear > 9999 || fileMonth > 12
           || fileMonth < 1 || fileDay > 31 || fileDay < 1) {
            cout << "ERROR BELOW: Typo in file date";
        }
        getline(inFileStream, newLineAfterDate); // handle newline character

        // -- handling headers --

        getline(inFileStream, headers); // used to store the value of the unused headers of the file

        // -- outputting headers --

        cout << "Region" << setw(6) << "Date" << setw(11) << "Codes" << setw(15) << "Dimensions"
        << setw(8) << "Color" << setw(15) << "Cust. Num." << endl;
        cout << LINE << endl;

        // -- input values --

        currentRow = 1;

        while (inFileStream >> state >> region >> orderYear >> dateDelimiter >>
               orderMonth >> dateDelimiter >> orderDay >> shapeCode
               >> materialCode >> radius >> height >> color >> customerNumber >>
               firstName >> lastName && getline(inFileStream, address)) {

            // -- validations --

            // orderDate

            if (orderYear < 1000 || orderYear > 9999 || orderMonth > 12
               || orderMonth < 1 || orderDay > 31 || orderDay < 1) {
                cout << "ERROR BELOW: Typo in order date" << endl;
                numErrors++;
            }
            if (orderYear > fileYear) {
                cout << "ERROR BELOW: order date is after file date" << endl;
                numErrors++;
            }
            else if (orderYear == fileYear && orderMonth > fileMonth) {
                cout << "ERROR BELOW: order date is after file date" << endl;
                numErrors++;
            }
            else if (orderYear == fileYear && orderMonth == fileMonth && orderDay > fileDay) {
                cout << "ERROR BELOW: order date is after file date" << endl;
                numErrors++;
            }

            // shapeCode

            if ((shapeCode != 'o') && (shapeCode != 'y') && (shapeCode != 'p')
                && (shapeCode != 'O') && (shapeCode != 'Y') && (shapeCode != 'P')) {
                cout << "ERROR BELOW: Not a legitimate shape." << endl;
                numErrors++;
            }

            // materialCode

            if ((materialCode != 'k') && (materialCode != 'a') && (materialCode != 'u')
              && (materialCode != 'K') && (materialCode != 'A') && (materialCode != 'U')) {
                cout << "ERROR BELOW: Not a legitimate material." << endl;
                numErrors++;
            }

            // radius

            if ((radius < 3) || (radius > 36)) {
                cout << "ERROR BELOW: The radius entered is outside of limits" << endl;
                numErrors++;
            }

            // height

            if ((shapeCode == 'o') || (shapeCode == 'y') || shapeCode == 'O' || shapeCode == 'Y'){
                if ((height < radius)  || (height > radius * 1.5)){
                  cout << "ERROR BELOW: The height entered is outside of limits" << endl;
                  numErrors++;
                }
            }

            // color

            if (!(color == "Red" || color == "Orange" || color == "Yellow" ||
                        color == "Green" || color == "Blue" ||
                        color == "Indigo" || color == "Violet")) {
                cout << "ERROR BELOW: invalid color." << endl;
                numErrors++;
            }

            // -- output non-calculated values --

            cout << setprecision(2) << fixed << setw(6) << region << setw(5)
            << orderYear << dateDelimiter << setw(2)
            << orderMonth << dateDelimiter << setw(2) << orderDay <<
            setw(3) << shapeCode << setw(3) << materialCode << setw(7) << radius;
            if (height == -1) {
                cout << setw(7) << "n/a" << setw(SPACER) << color <<
                setw(17) << customerNumber;
            }
            else {
                cout << setprecision(2) << fixed << setw(7) <<
                height << setw(SPACER) << color << setw(17) << customerNumber;
            }
            cout << endl;

            // -- CHECK IF ROW IS CORRECT --

            if (numErrorsBefore < numErrors) {
                rowsIncorrect++;
            }
            else {
                rowsCorrect++;

                loadSuccess = true;

                // -- SET DATA MEMBERS TO THIS ROW'S DATA
                Shape thisRow(region, shapeCode, materialCode, radius, height, color, customerNumber);
                vS.push_back(thisRow);
            }
            numErrorsBefore = numErrors;
        }
        currentRow++;
        numErrors = 0;
    }
    totalRecords = rowsCorrect + rowsIncorrect;
    totalRecordsL = vS.size();


    cout << "\nCounts: Total Records = " << totalRecords << "   Records with Errors = "
         << rowsIncorrect << "   Records without Errors = " << rowsCorrect << endl;
    cout << totalRecordsL << " records now loaded, " << rowsCorrect <<
         " added to vectors.\n\n" << endl;

    inFileStream.close();
}

void allDetails(const vector<Shape> &vS) {

    // -- VARIABLES --

    // ints

    int times = vS.size() - 1;


    // -- outputting headers --

    cout << "Region" << setw(11) << "Codes" << setw(15) << "Dimensions"
    << setw(8) << "Color" << setw(14) << "Cust. Num" << setw(8) << "Cost" << setw(12)
    << "Price" <<  setw(10) << "Profit" << endl;
    cout << LINE << endl;

    // -- LOOP THROUGH THE VECTORS

    for (int iterator = 0; iterator <= times; iterator++) {
        // -- output non-calculated values --

        cout << setprecision(2) << fixed << setw(5) << vS[iterator].getRegion() << setw(6) <<
        vS[iterator].getShapeCode() << setw(3) << vS[iterator].getMaterialCode()
        << setw(10) << vS[iterator].getRadius();
        if (vS[iterator].getHeight() == -1) {
            cout << setw(7) << "n/a";
        }
        else {
            cout << setprecision(2) << fixed << setw(7) << vS[iterator].getHeight();
        }
        cout << setw(SPACER) << vS[iterator].getColor();

        // -- calculated row outputs --

        cout << setprecision(2) << fixed << setw(13) << vS[iterator].getCustomerNumber()
        << setw(11) << vS[iterator].getManufacturingCost() << setw(11)
        << vS[iterator].getSalesPrice() << setw(11) << vS[iterator].getProfit() << endl;
    }
}
void customerDetails(const vector<Shape> &vS) {
     // -- VARIABLES --

    // ints

    int times = vS.size() - 1;

    // strings

    string customerNumber = "";

    // bools
    bool found = false;

    // -- PROMPT FOR INPUT --

    cout << "\n\n";
    cout << "Enter a customer ID: ";
    cin >> customerNumber;
    cin.ignore(500, '\n');

    // -- outputting headers --

    cout << "Region" << setw(11) << "Codes" << setw(15) << "Dimensions"
    << setw(8) << "Color" << setw(14) << "Cust. Num" << setw(8) << "Cost" << setw(12)
    << "Price" <<  setw(10) << "Profit" << endl;
    cout << LINE << endl;

    // -- TEST EACH CUSTOMER NUMBER AGAINST THE INPUT

    for(int iterator = 0; iterator <= times; iterator++) {
        if (vS[iterator].getCustomerNumber() == customerNumber) {
            found = true;

            // -- output non-calculated values --

            cout << setprecision(2) << fixed << setw(5) << vS[iterator].getRegion() << setw(6) <<
            vS[iterator].getShapeCode() << setw(3) << vS[iterator].getMaterialCode()
            << setw(10) << vS[iterator].getRadius();
            if (vS[iterator].getHeight() == -1) {
                cout << setw(7) << "n/a";
            }
            else {
                cout << setprecision(2) << fixed << setw(7) << vS[iterator].getHeight();
            }
            cout << setw(SPACER) << vS[iterator].getColor();

            // -- calculated row outputs --

            cout << setprecision(2) << fixed << setw(13) << vS[iterator].getCustomerNumber()
            << setw(11) << vS[iterator].getManufacturingCost() << setw(11)
            << vS[iterator].getSalesPrice() << setw(11) << vS[iterator].getProfit() << endl;
        }
    }
    if (found == false)
        cout << "      Customer number " << customerNumber << " not found."<< endl;
}
void summaryByShape(const vector<Shape> &vS) {

    // -- VARIABLES --

    // ints

    int times = vS.size() - 1;

    int coneNumber =      0;
    int cylinderNumber =  0;
    int sphereNumber =    0;

    // doubles

    double coneCost =        0.0;
    double conePrice =       0.0;
    double coneProfit =      0.0;

    double cylinderCost =    0.0;
    double cylinderPrice =   0.0;
    double cylinderProfit =  0.0;

    double sphereCost =      0.0;
    double spherePrice =     0.0;
    double sphereProfit =    0.0;

    double totalNumber =     0.0;
    double totalCost =       0.0;
    double totalPrice =      0.0;
    double totalProfit =     0.0;
    double averageNumber =   0.0;
    double averageCost =     0.0;
    double averagePrice =    0.0;
    double averageProfit =   0.0;

    // -- LOOP THROUGH THE VECTORS

    for (int iterator = 0; iterator <= times; iterator++) {

        // cylinder

        if (vS[iterator].getShapeCode() == 'y' ||
            vS[iterator].getShapeCode() == 'Y') {
            cylinderNumber++;
            cylinderCost = cylinderCost + vS[iterator].getManufacturingCost();
            cylinderPrice = cylinderPrice + vS[iterator].getSalesPrice();
            cylinderProfit = cylinderProfit + vS[iterator].getProfit();
        }

        // cone

        else if (vS[iterator].getShapeCode() == 'o' ||
                 vS[iterator].getShapeCode() == 'O') {
            coneNumber++;
            coneCost = coneCost + vS[iterator].getManufacturingCost();
            conePrice = conePrice + vS[iterator].getSalesPrice();
            coneProfit = coneProfit + vS[iterator].getProfit();
        }

        // sphere

        else if (vS[iterator].getShapeCode() == 'p' ||
                 vS[iterator].getShapeCode() == 'P') {
            sphereNumber++;
            sphereCost = sphereCost + vS[iterator].getManufacturingCost();
            spherePrice = spherePrice + vS[iterator].getSalesPrice();
            sphereProfit = sphereProfit + vS[iterator].getProfit();
        }

        // -- totals incrementing --

        totalNumber++;
        totalCost = totalCost + vS[iterator].getManufacturingCost();
        totalPrice = totalPrice + vS[iterator].getSalesPrice();
        totalProfit += vS[iterator].getProfit();

    }

    // -- calculate averages --

    averageNumber = totalNumber / 3;
    averageCost = totalCost / 3;
    averagePrice = totalPrice / 3;
    averageProfit = totalProfit / 3;

    // -- summary outputs --

    cout << setw(50) << "Total" << endl;
    cout << setw(8) << "Shape" << setw(10) << "Number" << setw(15) << "Cost" <<
    setw(20) << "Price" << setw(20) << "Profit" << endl;

    cout << LINE << endl;
    cout << setprecision(2) << fixed << setw(8) << "Cone" << setw(7) << coneNumber <<
    setw(20) << coneCost << setw(20) << conePrice << setw(20) << coneProfit << endl;
    cout << setprecision(2) << fixed << setw(8) << "Cylinder" << setw(7) <<
    cylinderNumber << setw(20) << cylinderCost << setw(20) << cylinderPrice <<
    setw(20) << cylinderProfit << endl;
    cout << setprecision(2) << fixed << setw(8) << "Sphere" << setw(7) <<
    sphereNumber << setw(20) << sphereCost << setw(20) << spherePrice << setw(20) <<
    sphereProfit << endl;
    cout << LINE << endl;
    cout << setw(8) << "Average" << setw(7) << setprecision(0) << averageNumber <<
    setw(20) << setprecision(2) << averageCost << setw(20) << setprecision(2) <<
    averagePrice << setw(20) << setprecision(2) << averageProfit << endl;
}

void summaryByRegion(const vector<Shape> &vS) {
    // -- VARIABLES --

    // ints

    int times = vS.size() - 1;

    int northNumber =        0;
    int westNumber =         0;
    int southNumber =        0;
    int eastNumber =         0;
    int otherNumber =        0;

    // doubles

    double northCost =        0.0;
    double northPrice =       0.0;
    double northProfit =      0.0;

    double westCost =    0.0;
    double westPrice =   0.0;
    double westProfit =  0.0;

    double southCost =      0.0;
    double southPrice =     0.0;
    double southProfit =    0.0;

    double eastCost =    0.0;
    double eastPrice =   0.0;
    double eastProfit =  0.0;

    double otherCost =      0.0;
    double otherPrice =     0.0;
    double otherProfit =    0.0;

    double totalNumber =     0.0;
    double totalCost =       0.0;
    double totalPrice =      0.0;
    double totalProfit =     0.0;
    double averageNumber =   0.0;
    double averageCost =     0.0;
    double averagePrice =    0.0;
    double averageProfit =   0.0;

    // -- LOOP THROUGH THE VECTORS

    for (int iterator = 0; iterator <= times; iterator++) {

        // south

        if (vS[iterator].getRegion() == "South") {
            southNumber++;
            southCost += vS[iterator].getManufacturingCost();
            southPrice += vS[iterator].getSalesPrice();
            southProfit += vS[iterator].getProfit();
        }

        // west

        else if (vS[iterator].getRegion() == "West") {
            westNumber++;
            westCost = westCost + vS[iterator].getManufacturingCost();
            westPrice = westPrice + vS[iterator].getSalesPrice();
            westProfit = westProfit + vS[iterator].getProfit();
        }


        // east

        else if (vS[iterator].getRegion() == "East") {
            eastNumber++;
            eastCost = eastCost + vS[iterator].getManufacturingCost();
            eastPrice = eastPrice + vS[iterator].getSalesPrice();
            eastProfit = eastProfit + vS[iterator].getProfit();
        }

        // other

        else if (vS[iterator].getRegion() == "Other") {
            otherNumber++;
            otherCost = otherCost + vS[iterator].getManufacturingCost();
            otherPrice = otherPrice + vS[iterator].getSalesPrice();
            otherProfit = otherProfit + vS[iterator].getProfit();
        }

        // north

        else if (vS[iterator].getRegion() == "North") {
            northNumber++;
            northCost = northCost + vS[iterator].getManufacturingCost();
            northPrice = northPrice + vS[iterator].getSalesPrice();
            northProfit = northProfit + vS[iterator].getProfit();
        }

        // -- totals incrementing --

        totalNumber++;
        totalCost = totalCost + vS[iterator].getManufacturingCost();
        totalPrice = totalPrice + vS[iterator].getSalesPrice();
        totalProfit += vS[iterator].getProfit();

    }

    // -- calculate averages --

    averageNumber = totalNumber / 5;
    averageCost = totalCost / 5;
    averagePrice = totalPrice / 5;
    averageProfit = totalProfit / 5;

    // -- summary outputs --

    cout << setw(50) << "Total" << endl;
    cout << setw(10) << "Region" << setw(10) << "Number" << setw(15) << "Cost" <<
    setw(20) << "Price" << setw(20) << "Profit" << endl;

    cout << LINE << endl;

    cout << setprecision(2) << fixed << setw(8) << "South" << setw(7) << southNumber <<
    setw(20) << southCost << setw(20) << southPrice << setw(20) << southProfit << endl;

    cout << setprecision(2) << fixed << setw(8) << "West" << setw(7) << westNumber <<
    setw(20) << westCost << setw(20) << westPrice << setw(20) << westProfit << endl;

    cout << setprecision(2) << fixed << setw(8) << "East" << setw(7) << eastNumber <<
    setw(20) << eastCost << setw(20) << eastPrice << setw(20) << eastProfit << endl;

    cout << setprecision(2) << fixed << setw(8) << "North" << setw(7) << northNumber <<
    setw(20) << northCost << setw(20) << northPrice << setw(20) << northProfit << endl;

    cout << setprecision(2) << fixed << setw(8) << "Other" << setw(7) << otherNumber <<
    setw(20) << otherCost << setw(20) << otherPrice << setw(20) << otherProfit << endl;

    cout << LINE << endl;

    cout << setw(8) << "Average" << setw(7) << setprecision(0) << averageNumber <<
    setw(20) << setprecision(2) << averageCost << setw(20) << setprecision(2) <<
    averagePrice << setw(20) << setprecision(2) << averageProfit << endl;
}
