#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <cctype>
#include <regex>

using namespace std;

int main(){
    float min_acres = 0.00;
    float max_acres = 0.00;
    int max_homesize = 0;
    int min_homesize = 0;
    int max_price = 0;
    int bed_min = 0;
    int bed_max = 0;
    float bathroom_min = 0.0;
    float bathroom_max = 0.0;
    int bed_importance = 0;
    int bathroom_importance = 0;
    int homesize_Importance = 0;
    int acre_importance = 0;
    int price_importance = 0;
    bool valid_homesize_min = false;
    bool valid_homesize_max = false;
    bool valid_max_price = false;
    bool valid_acre_min = false;
    bool valid_acre_max = false;
    bool valid_state = false;
    bool valid_bath_min = false;
    bool valid_bath_max = false;
    bool valid_bed_min = false;
    bool valid_bed_max = false;
    bool valid_bed_importance = false;
    bool valid_bathroom_importance = false;
    bool valid_homesize_importance = false;
    bool valid_acre_importance = false;
    bool valid_price_importance = false;
    string State;
    string city;
    static const regex tester("^[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?$");
    while(valid_state == false){
        cout << "Available States: Pennsylvania, New Jersey, New York" << endl;
        cout << "Enter a State: ";
        getline(std::cin, State);
        if(State == "Pennsylvania" || State == "New Jersey" || State == "New York"){
            valid_state = true;
        }
        else{
            cout << "Invalid State" << endl;
        }
    }

    while(valid_bath_min == false){
        cout << "Mininum number of bathrooms: ";
        string temp;
        cin >> temp;
        if(regex_match(temp, tester) == true){
            bathroom_min = stod(temp);
            valid_bath_min = true;
        }
        else{
            cout << "Invalid Input" << endl;
        }
    }

    while(valid_bath_max == false){
        cout << "Maximum number of bathrooms: ";
        string temp;
        cin >> temp;
        if(regex_match(temp, tester) == true){
            bathroom_max = stod(temp);
            if(bathroom_max >= bathroom_min){
                valid_bath_max = true;
            }
            else{
                cout << "Invalid Input. Max number of bathrooms has to be bigger than or equal to the minimum." << endl;
            }
        }
        else{
            cout << "Invalid Input" << endl;
        }
    }

    while(valid_bed_min == false){
        cout << "Mininum number of bedrooms: ";
        string temp;
        cin >> temp;
        if(regex_match(temp, tester) == true){
            bed_min = stoi(temp);
            valid_bed_min = true;
        }
        else{
            cout << "Invalid Input" << endl;
        }
    }

    while(valid_bed_max == false){
        cout << "Maximum number of bedrooms: ";
        string temp;
        cin >> temp;
        if(regex_match(temp, tester) == true){
            bed_max = stoi(temp);
            if(bed_max >= bed_min){
                valid_bed_max = true;
            }
            else{
                cout << "Invalid Input. Max number of bedrooms has to be bigger than or equal to the minimum." << endl;
            }
        }
        else{
            cout << "Invalid Input" << endl;
        }
    }

    while(valid_acre_min == false){
        cout << "Mininum acreage: ";
        string temp;
        cin >> temp;
        if(regex_match(temp, tester) == true){
            min_acres = stod(temp);
            valid_acre_min = true;
        }
        else{
            cout << "Invalid Input" << endl;
        }
    }

    while(valid_acre_max == false){
        cout << "Maximum acreage: ";
        string temp;
        cin >> temp;
        if(regex_match(temp, tester) == true){
            max_acres = stod(temp);
            if(max_acres >= min_acres){
                valid_acre_max = true;
            }
            else{
                cout << "Invalid Input. Max acreage must be greater than or equal to the minimum." << endl;
            }
        }
        else{
            cout << "Invalid Input" << endl;
        }
    }

    while(valid_homesize_min == false){
        cout << "Minimum square footage of house (In Square feet): ";
        string temp;
        cin >> temp;
        if(regex_match(temp, tester) == true){
            min_homesize = stoi(temp);
            valid_homesize_min = true;
        }
        else{
            cout << "Invalid Input" << endl;
        }
    }

    while(valid_homesize_max == false){
        cout << "Maximum square footage of house (In Square feet): ";
        string temp;
        cin >> temp;
        if(regex_match(temp, tester) == true){
            max_homesize = stod(temp);
            if(max_homesize >= min_homesize){
                valid_homesize_max = true;
            }
            else{
                cout << "Invalid Input. Max square footage of the house must be greater than or equal to the minimum." << endl;
            }
        }
        else{
            cout << "Invalid Input" << endl;
        }
    }

    while(valid_max_price == false){
        cout << "Maximum price: ";
        string temp;
        cin >> temp;
        if(regex_match(temp, tester) == true){
            max_price = stoi(temp);
            valid_max_price = true;
        }
        else{
            cout << "Invalid Input" << endl;
        }
    }

    static const regex importance_tester("^(10|[1-9])$");
    while(valid_bathroom_importance == false){
        cout << "How important is having more bathrooms? (Enter a number 1-10): ";
        string temp;
        cin >> temp;
        if(regex_match(temp, importance_tester) == true){
            bathroom_importance = stoi(temp);
            valid_bathroom_importance = true;
        }
        else{
            cout << "Invalid Input" << endl;
        }
    }

    while(valid_bed_importance == false){
        cout << "How important is having more bedrooms? (Enter a number 1-10): ";
        string temp;
        cin >> temp;
        if(regex_match(temp, importance_tester) == true){
            bed_importance = stoi(temp);
            valid_bed_importance = true;
        }
        else{
            cout << "Invalid Input" << endl;
        }
    }

    while(valid_acre_importance == false){
        cout << "How important is having more acres? (Enter a number 1-10): ";
        string temp;
        cin >> temp;
        if(regex_match(temp, importance_tester) == true){
            acre_importance = stoi(temp);
            valid_acre_importance = true;
        }
        else{
            cout << "Invalid Input" << endl;
        }
    }

    while(valid_homesize_importance == false){
        cout << "How important is having a larger home size (In square foot)? (Enter a number 1-10): ";
        string temp;
        cin >> temp;
        if(regex_match(temp, importance_tester) == true){
            homesize_Importance = stoi(temp);
            valid_homesize_importance = true;
        }
        else{
            cout << "Invalid Input" << endl;
        }
    }

    while(valid_price_importance == false){
        cout << "How important is having a lower price? (Enter a number 1-10): ";
        string temp;
        cin >> temp;
        if(regex_match(temp, importance_tester) == true){
            price_importance = stoi(temp);
            valid_price_importance = true;
        }
        else{
            cout << "Invalid Input" << endl;
        }
    }

    fstream file("DataSet.csv");
    unordered_map<string,vector<string>> dataset;
    string line;
    int counter = 0;
    int temp_counter = 0;
    while ((getline(file,line))) {
        bool eligibility = true;
        while(eligibility == true){
            temp_counter += 1;
            string num_bedrooms_string, num_bathrooms_string, acres_string, city_string, state_string, house_size_string, price_string;
            stringstream str(line);
            getline(str, num_bedrooms_string, ',');
            getline(str, num_bathrooms_string, ',');
            getline(str, acres_string, ',');
            getline(str, city_string, ',');
            getline(str, state_string, ',');
            getline(str, house_size_string, ',');
            str >> price_string;

            if (num_bathrooms_string == "") {
                num_bathrooms_string = "0.0";
            }
            if (num_bedrooms_string == "") {
                num_bedrooms_string = "0";
            }
            if (acres_string == "") {
                acres_string = "0.00";
            }
            if (house_size_string == "") {
                house_size_string = "0";
            }
            if (state_string != State){
                eligibility = false;
                break;
            }
            if (stod(num_bathrooms_string) > bathroom_max || stod(num_bathrooms_string) < bathroom_min){
                eligibility = false;
                break;
            }
            if(stoi(num_bedrooms_string) > bed_max || stoi(num_bedrooms_string) < bed_min){
                eligibility = false;
                break;
            }
            if(stod(acres_string) > max_acres || stod(acres_string) < min_acres) {
                eligibility = false;
                break;
            }
            if(stoi(house_size_string) > max_homesize || stoi(house_size_string) < min_homesize){
                eligibility = false;
                break;
            }
            if(stoi(price_string) > max_price){
                eligibility = false;
                break;
            }
            int bath_score = 0;
            int bed_score = 0;
            int acreage_score = 0;
            int feet_score = 0;
            int price_score = 0;

            bath_score = (stod(num_bathrooms_string)/bathroom_max) * 10;
            if(bath_score == 0){
                bath_score = 1;
            }
            bed_score = (stod(num_bedrooms_string)/bed_max) * 10;
            if(bed_score == 0){
                bed_score = 1;
            }
            acreage_score = (stod(acres_string)/max_acres) * 10;
            if(acreage_score == 0){
                acreage_score = 1;
            }
            feet_score = (stod(house_size_string)/max_homesize) * 10;
            if(feet_score == 0){
                feet_score = 1;
            }
            price_score = 10 - ((stod(price_string)/max_price) * 10);
            if(price_score == 0){
                price_score = 1;
            }

            bed_score = bed_score * bed_importance;
            bath_score = bath_score * bathroom_importance;
            acreage_score = acreage_score * acre_importance;
            feet_score = feet_score * homesize_Importance;
            price_score = price_score * price_importance;
            int total_currentScore = 0;
            total_currentScore = bed_score + bath_score + acreage_score + feet_score + price_score;
            cout << total_currentScore << endl;
            string current_house_name = "House " + to_string(temp_counter);
            cout << current_house_name << endl;
            vector<string> home_attributes; //Order is: Home score, Price, State, City, Num of Beds, Num of Baths, Acres, and home size.
            home_attributes.push_back(to_string(total_currentScore));
            home_attributes.push_back(price_string);
            home_attributes.push_back(state_string);
            home_attributes.push_back(city_string);
            home_attributes.push_back(num_bedrooms_string);
            home_attributes.push_back(num_bathrooms_string);
            home_attributes.push_back(acres_string);
            home_attributes.push_back(house_size_string);
            dataset[current_house_name] = home_attributes;
            counter += 1;
            eligibility = false;
            /*cout << num_bedrooms_string << endl;
            cout << num_bathrooms_string << endl;
            cout << acres_string << endl;
            cout << city_string << endl;
            cout << state_string << endl;
            cout << house_size_string << endl;
            cout << price_string << endl;*/
        }
    }
    cout << counter << endl;
    return 0;
}

//bed,bath,acre_lot,city,state,house_size,price
