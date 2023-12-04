#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <cctype>
#include <regex>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <cmath>
using namespace std;

class Homes_Sorter{
private:
    unordered_map<string,vector<string>> dataset;
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
    long long time_merge;
    long long time_quick;
    vector<string> merge_rankings;
    vector<string> quick_rankings;
    vector<string> merge_sort_vector;
public:
    void insert(string state_string,string city_string, string num_bathrooms_string, string num_bedrooms_string, string acres_string, string house_size_string, string price_string, int temp_counter)
    //insert function that takes data form dataset and insert them if they meet user parameters
    {
        if (state_string != State){
            return;
        }
        if (stod(num_bathrooms_string) > bathroom_max || stod(num_bathrooms_string) < bathroom_min){
            return;
        }
        if(stoi(num_bedrooms_string) > bed_max || stoi(num_bedrooms_string) < bed_min){
            return;
        }
        if(stod(acres_string) > max_acres || stod(acres_string) < min_acres) {
            return;

        }
        if(stoi(house_size_string) > max_homesize || stoi(house_size_string) < min_homesize){
            return;
        }
        if(stoi(price_string) > max_price){
            return;
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
        string current_house_name = "House " + to_string(temp_counter);
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
    }

    void filter_data()
    //function that goes through data in Dataset and places each values into insert function
    {
        fstream file("Files/DataSet.csv");
        string line;
        int temp_counter = 0;
        while ((getline(file,line))) {
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
            insert(state_string, city_string,num_bathrooms_string, num_bedrooms_string, acres_string,house_size_string, price_string,temp_counter);
        }
        MergeSort();
        quicksort();
    }

    void results(){
        filter_data();
        sf::RenderWindow results_window(sf::VideoMode(1200, 1000), "HOMIE");
        sf::RectangleShape results_rect;
        results_rect.setSize(sf::Vector2f(1200, 1000));
        results_rect.setPosition(0, 0);
        results_rect.setOrigin(0, 0);
        results_rect.setFillColor(sf::Color(137, 148, 153));
        results_window.setFramerateLimit(30);

        sf::Font font;
        font.loadFromFile("Files/font.ttf");

        sf::Text Title;
        Title.setString("Home Locater");
        Title.setFont(font);
        Title.setCharacterSize(28);
        Title.setFillColor(sf::Color::White);
        Title.setStyle(sf::Text::Bold);
        sf::FloatRect TitletextRect = Title.getLocalBounds();
        Title.setOrigin(TitletextRect.left + TitletextRect.width / 2.0f,TitletextRect.top  + TitletextRect.height / 2.0f);
        Title.setPosition(results_window.getSize().x/2.0f,results_window.getSize().y/2.0f - 385);

        sf::Text Results_page;
        Results_page.setString("Best Match");
        Results_page.setFont(font);
        Results_page.setCharacterSize(22);
        Results_page.setFillColor(sf::Color::White);
        Results_page.setStyle(sf::Text::Bold);
        sf::FloatRect Results_pageRect = Results_page.getLocalBounds();
        Results_page.setOrigin(Results_pageRect.left + Results_pageRect.width / 2.0f,Results_pageRect.top  + Results_pageRect.height / 2.0f);
        Results_page.setPosition(results_window.getSize().x/2.0f,results_window.getSize().y/2.0f - 350);

        sf::Text Noresults;
        Noresults.setString("NO HOMES FOUND");
        Noresults.setFont(font);
        Noresults.setCharacterSize(40);
        Noresults.setFillColor(sf::Color::Red);
        Noresults.setStyle(sf::Text::Bold);
        sf::FloatRect NoresultsRect = Noresults.getLocalBounds();
        Noresults.setOrigin(NoresultsRect.left + NoresultsRect.width / 2.0f,NoresultsRect.top  + NoresultsRect.height / 2.0f);
        Noresults.setPosition(results_window.getSize().x/2.0f,results_window.getSize().y/2.0f);

        sf::Text Merge_Sort_TIME;
        Merge_Sort_TIME.setString("Merge Sort Time: " + to_string(time_merge) + " milliseconds");
        Merge_Sort_TIME.setFont(font);
        Merge_Sort_TIME.setCharacterSize(20);
        Merge_Sort_TIME.setFillColor(sf::Color::White);
        Merge_Sort_TIME.setStyle(sf::Text::Bold);
        sf::FloatRect Merge_Sort_TIMERect = Merge_Sort_TIME.getLocalBounds();
        Merge_Sort_TIME.setOrigin(Merge_Sort_TIMERect.left + Merge_Sort_TIMERect.width / 2.0f,Merge_Sort_TIMERect.top  + Merge_Sort_TIMERect.height / 2.0f);
        Merge_Sort_TIME.setPosition(results_window.getSize().x/2.0f - 325,results_window.getSize().y/2.0f + 230);

        sf::Text Quick_Sort_TIME;
        Quick_Sort_TIME.setString("Quick Sort Time: " + to_string(time_quick) + " milliseconds");
        Quick_Sort_TIME.setFont(font);
        Quick_Sort_TIME.setCharacterSize(20);
        Quick_Sort_TIME.setFillColor(sf::Color::White);
        Quick_Sort_TIME.setStyle(sf::Text::Bold);
        sf::FloatRect Quick_Sort_TIME_TIMERect = Merge_Sort_TIME.getLocalBounds();
        Quick_Sort_TIME.setOrigin(Quick_Sort_TIME_TIMERect.left + Quick_Sort_TIME_TIMERect.width / 2.0f,Quick_Sort_TIME_TIMERect.top  + Quick_Sort_TIME_TIMERect.height / 2.0f);
        Quick_Sort_TIME.setPosition(results_window.getSize().x/2.0f - 325,results_window.getSize().y/2.0f + 200);

        sf::Texture Reset_Button;
        Reset_Button.loadFromFile("Files/Images/HOMERESET_B.png");
        sf::Sprite Reset_Button_image(Reset_Button);
        sf::FloatRect Reset_Button_Bounds = Reset_Button_image.getLocalBounds();
        Reset_Button_image.setOrigin(Reset_Button_Bounds.left + Reset_Button_Bounds.width / 2.0f,Reset_Button_Bounds.top  + Reset_Button_Bounds.height / 2.0f);
        Reset_Button_image.setPosition(results_window.getSize().x/2.0f,results_window.getSize().y/2.0f + 350);

        sf::Texture Homeless_IMAGE;
        Homeless_IMAGE.loadFromFile("Files/Images/Homeless.PNG");
        sf::Sprite Homeless_IMAGE_image(Homeless_IMAGE);
        sf::FloatRect Homeless_IMAGE_Bounds = Homeless_IMAGE_image.getLocalBounds();
        Homeless_IMAGE_image.setOrigin(Homeless_IMAGE_Bounds.left + Homeless_IMAGE_Bounds.width / 2.0f,Homeless_IMAGE_Bounds.top  + Homeless_IMAGE_Bounds.height / 2.0f);
        Homeless_IMAGE_image.setPosition(results_window.getSize().x/2.0f,results_window.getSize().y/2.0f);

        sf::Texture House_1;
        House_1.loadFromFile("Files/Images/Diamond1_House.png");
        sf::Sprite House_1image(House_1);
        sf::FloatRect House_1Bounds = House_1image.getLocalBounds();
        House_1image.setOrigin(House_1Bounds.left + House_1Bounds.width / 2.0f,House_1Bounds.top  + House_1Bounds.height / 2.0f);
        House_1image.setPosition(results_window.getSize().x/2.0f - 450,results_window.getSize().y/2.0f - 250);

        sf::Texture House_2;
        House_2.loadFromFile("Files/Images/House_2.jpg");
        sf::Sprite House_2image(House_2);
        sf::FloatRect House_2Bounds = House_2image.getLocalBounds();
        House_2image.setOrigin(House_2Bounds.left + House_2Bounds.width / 2.0f,House_2Bounds.top  + House_2Bounds.height / 2.0f);
        House_2image.setPosition(results_window.getSize().x/2.0f - 450,results_window.getSize().y/2.0f - 75);

        sf::Texture House_3;
        House_3.loadFromFile("Files/Images/House_3.jpeg");
        sf::Sprite House_3image(House_3);
        sf::FloatRect House_3Bounds = House_3image.getLocalBounds();
        House_3image.setOrigin(House_3Bounds.left + House_3Bounds.width / 2.0f,House_3Bounds.top  + House_3Bounds.height / 2.0f);
        House_3image.setPosition(results_window.getSize().x/2.0f - 450,results_window.getSize().y/2.0f + 100);

        sf::Text House_1_Top;
        House_1_Top.setString("");
        House_1_Top.setFont(font);
        House_1_Top.setCharacterSize(14);
        House_1_Top.setFillColor(sf::Color::White);
        House_1_Top.setStyle(sf::Text::Bold);
        sf::FloatRect House_1_TopRect = House_1_Top.getLocalBounds();
        House_1_Top.setOrigin(House_1_TopRect.left + House_1_TopRect.width / 2.0f,House_1_TopRect.top  + House_1_TopRect.height / 2.0f);
        House_1_Top.setPosition(results_window.getSize().x/2.0f - 350,results_window.getSize().y/2.0f - 280);

        sf::Text House_1_Price;
        House_1_Price.setString("");
        House_1_Price.setFont(font);
        House_1_Price.setCharacterSize(20);
        House_1_Price.setFillColor(sf::Color::White);
        House_1_Price.setStyle(sf::Text::Bold);
        sf::FloatRect House_1_PriceRect = House_1_Price.getLocalBounds();
        House_1_Price.setOrigin(House_1_TopRect.left + House_1_TopRect.width / 2.0f,House_1_TopRect.top  + House_1_TopRect.height / 2.0f);
        House_1_Price.setPosition(results_window.getSize().x/2.0f - 350,results_window.getSize().y/2.0f - 250);

        sf::Text House_2_Top;
        House_2_Top.setString("");
        House_2_Top.setFont(font);
        House_2_Top.setCharacterSize(14);
        House_2_Top.setFillColor(sf::Color::White);
        House_2_Top.setStyle(sf::Text::Bold);
        sf::FloatRect House_2_TopRect = House_2_Top.getLocalBounds();
        House_2_Top.setOrigin(House_1_TopRect.left + House_1_TopRect.width / 2.0f,House_1_TopRect.top  + House_1_TopRect.height / 2.0f);
        House_2_Top.setPosition(results_window.getSize().x/2.0f - 350,results_window.getSize().y/2.0f - 105);

        sf::Text House_2_Price;
        House_2_Price.setString("");
        House_2_Price.setFont(font);
        House_2_Price.setCharacterSize(20);
        House_2_Price.setFillColor(sf::Color::White);
        House_2_Price.setStyle(sf::Text::Bold);
        sf::FloatRect House_2_PriceRect = House_2_Price.getLocalBounds();
        House_2_Price.setOrigin(House_1_TopRect.left + House_1_TopRect.width / 2.0f,House_1_TopRect.top  + House_1_TopRect.height / 2.0f);
        House_2_Price.setPosition(results_window.getSize().x/2.0f - 350,results_window.getSize().y/2.0f - 75);

        sf::Text House_3_Top;
        House_3_Top.setString("");
        House_3_Top.setFont(font);
        House_3_Top.setCharacterSize(14);
        House_3_Top.setFillColor(sf::Color::White);
        House_3_Top.setStyle(sf::Text::Bold);
        sf::FloatRect House_3_TopRect = House_3_Top.getLocalBounds();
        House_3_Top.setOrigin(House_1_TopRect.left + House_1_TopRect.width / 2.0f,House_1_TopRect.top  + House_1_TopRect.height / 2.0f);
        House_3_Top.setPosition(results_window.getSize().x/2.0f - 350,results_window.getSize().y/2.0f + 70);

        sf::Text House_3_Price;
        House_3_Price.setString("");
        House_3_Price.setFont(font);
        House_3_Price.setCharacterSize(20);
        House_3_Price.setFillColor(sf::Color::White);
        House_3_Price.setStyle(sf::Text::Bold);
        sf::FloatRect House_3_PriceRect = House_3_Price.getLocalBounds();
        House_3_Price.setOrigin(House_1_TopRect.left + House_1_TopRect.width / 2.0f,House_1_TopRect.top  + House_1_TopRect.height / 2.0f);
        House_3_Price.setPosition(results_window.getSize().x/2.0f - 350,results_window.getSize().y/2.0f + 100);

        while (results_window.isOpen()) {
            sf::Event event;
            while (results_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    results_window.close();
                if (event.type == sf::Event::MouseButtonPressed){
                    if (event.key.code == sf::Mouse::Left) {
                        sf::Vector2i pos = sf::Mouse::getPosition(results_window);
                        if (Reset_Button_image.getGlobalBounds().contains(static_cast<float>(pos.x), static_cast<float>(pos.y))){
                            reset();
                            results_window.close();
                            main_screen();
                        }
                    }
                }
            }
            results_window.clear();
            results_window.draw(results_rect);
            results_window.draw(Title);
            results_window.draw(Reset_Button_image);
            if(merge_sort_vector.size() > 0){
                results_window.draw(Results_page);
                results_window.draw(Merge_Sort_TIME);
                results_window.draw(Quick_Sort_TIME);
                if(merge_sort_vector.size() == 1){
                    House_1_Top.setString(merge_sort_vector[0] + ", " + dataset[merge_sort_vector[0]].at(3) + ", " + dataset[merge_sort_vector[0]].at(2)+ ", " + dataset[merge_sort_vector[0]].at(4) + " Bedrooms"  + ", " + dataset[merge_sort_vector[0]].at(5) + " Bathrooms" + ", " + dataset[merge_sort_vector[0]].at(7) + " Square Feet" ", " + dataset[merge_sort_vector[0]].at(6) + " Acres");
                    House_1_Price.setString("$" + dataset[merge_sort_vector[0]].at(1));
                    results_window.draw(House_1image);
                    results_window.draw(House_1_Top);
                    results_window.draw(House_1_Price);
                }
                else if(merge_sort_vector.size() == 2){
                    House_1_Top.setString(merge_sort_vector[0] + ", " + dataset[merge_sort_vector[0]].at(3) + ", " + dataset[merge_sort_vector[0]].at(2)+ ", " + dataset[merge_sort_vector[0]].at(4) + " Bedrooms"  + ", " + dataset[merge_sort_vector[0]].at(5) + " Bathrooms" + ", " + dataset[merge_sort_vector[0]].at(7) + " Square Feet" ", " + dataset[merge_sort_vector[0]].at(6) + " Acres");
                    House_1_Price.setString("$" + dataset[merge_sort_vector[0]].at(1));
                    House_2_Top.setString(merge_sort_vector[1] + ", " + dataset[merge_sort_vector[1]].at(3) + ", " + dataset[merge_sort_vector[1]].at(2)+ ", " + dataset[merge_sort_vector[1]].at(4) + " Bedrooms"  + ", " + dataset[merge_sort_vector[1]].at(5) + " Bathrooms" + ", " + dataset[merge_sort_vector[1]].at(7) + " Square Feet" ", " + dataset[merge_sort_vector[1]].at(6) + " Acres");
                    House_2_Price.setString("$" + dataset[merge_sort_vector[1]].at(1));
                    results_window.draw(House_1image);
                    results_window.draw(House_2image);
                    results_window.draw(House_1_Top);
                    results_window.draw(House_1_Price);
                    results_window.draw(House_2_Top);
                    results_window.draw(House_2_Price);
                }
                else if(merge_sort_vector.size() >= 3){
                    House_1_Top.setString(merge_sort_vector[0] + ", " + dataset[merge_sort_vector[0]].at(3) + ", " + dataset[merge_sort_vector[0]].at(2)+ ", " + dataset[merge_sort_vector[0]].at(4) + " Bedrooms"  + ", " + dataset[merge_sort_vector[0]].at(5) + " Bathrooms" + ", " + dataset[merge_sort_vector[0]].at(7) + " Square Feet" ", " + dataset[merge_sort_vector[0]].at(6) + " Acres");
                    House_1_Price.setString("$" + dataset[merge_sort_vector[0]].at(1));
                    House_2_Top.setString(merge_sort_vector[1] + ", " + dataset[merge_sort_vector[1]].at(3) + ", " + dataset[merge_sort_vector[1]].at(2)+ ", " + dataset[merge_sort_vector[1]].at(4) + " Bedrooms"  + ", " + dataset[merge_sort_vector[1]].at(5) + " Bathrooms" + ", " + dataset[merge_sort_vector[1]].at(7) + " Square Feet" ", " + dataset[merge_sort_vector[1]].at(6) + " Acres");
                    House_2_Price.setString("$" + dataset[merge_sort_vector[1]].at(1));
                    House_3_Top.setString(merge_sort_vector[2] + ", " + dataset[merge_sort_vector[2]].at(3) + ", " + dataset[merge_sort_vector[2]].at(2)+ ", " + dataset[merge_sort_vector[2]].at(4) + " Bedrooms"  + ", " + dataset[merge_sort_vector[2]].at(5) + " Bathrooms" + ", " + dataset[merge_sort_vector[2]].at(7) + " Square Feet" ", " + dataset[merge_sort_vector[2]].at(6) + " Acres");
                    House_3_Price.setString("$" + dataset[merge_sort_vector[2]].at(1));
                    results_window.draw(House_1image);
                    results_window.draw(House_2image);
                    results_window.draw(House_3image);
                    results_window.draw(House_1_Top);
                    results_window.draw(House_1_Price);
                    results_window.draw(House_2_Top);
                    results_window.draw(House_2_Price);
                    results_window.draw(House_3_Top);
                    results_window.draw(House_3_Price);
                }
            }
            else if (merge_sort_vector.size() == 0){
                results_window.draw(Homeless_IMAGE_image);
                results_window.draw(Noresults);
            }
            results_window.display();
        }
    }


    void reset()
    //reset function that set values back to default ready for next input
    {
        min_acres = 0.00;
        max_acres = 0.00;
        max_homesize = 0;
        min_homesize = 0;
        max_price = 0;
        bed_min = 0;
        bed_max = 0;
        bathroom_min = 0.0;
        bathroom_max = 0.0;
        bed_importance = 0;
        bathroom_importance = 0;
        homesize_Importance = 0;
        acre_importance = 0;
        price_importance = 0;
        valid_homesize_min = false;
        valid_homesize_max = false;
        valid_max_price = false;
        valid_acre_min = false;
        valid_acre_max = false;
        valid_state = false;
        valid_bath_min = false;
        valid_bath_max = false;
        valid_bed_min = false;
        valid_bed_max = false;
        valid_bed_importance = false;
        valid_bathroom_importance = false;
        valid_homesize_importance = false;
        valid_acre_importance = false;
        valid_price_importance = false;
        State = "";
        city = "";
        time_merge = 0;
        time_quick = 0;
        dataset.clear();
        merge_rankings.clear();
        merge_sort_vector.clear();
        quick_rankings.clear();
    }

    void main_screen()
    //main screen function that displays survey to all for user to insert paramters
    {
        sf::RenderWindow window(sf::VideoMode(1200, 1000), "HOMIE");
        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f(1200,1000));
        rect.setPosition(0,0);
        rect.setOrigin(0,0);
        rect.setFillColor(sf::Color(137,148,153));
        window.setFramerateLimit(30);

        sf::Font font;
        font.loadFromFile("Files/font.ttf");

        sf::Text Title;
        Title.setString("Home Locater");
        Title.setFont(font);
        Title.setCharacterSize(28);
        Title.setFillColor(sf::Color::White);
        Title.setStyle(sf::Text::Bold);
        sf::FloatRect TitletextRect = Title.getLocalBounds();
        Title.setOrigin(TitletextRect.left + TitletextRect.width / 2.0f,TitletextRect.top  + TitletextRect.height / 2.0f);
        Title.setPosition(window.getSize().x/2.0f,window.getSize().y/2.0f - 385);

        sf::Text Prompttext;
        Prompttext.setString("Available States: Pennsylvania, New York, New Jersey");
        Prompttext.setFont(font);
        Prompttext.setCharacterSize(18);
        Prompttext.setFillColor(sf::Color::White);
        Prompttext.setStyle(sf::Text::Bold);
        sf::FloatRect PrompttextRect = Prompttext.getLocalBounds();
        Prompttext.setOrigin(PrompttextRect.left + PrompttextRect.width / 2.0f,PrompttextRect.top  + PrompttextRect.height / 2.0f);
        Prompttext.setPosition(window.getSize().x/2.0f - 250,window.getSize().y/2.0f - 350);


        sf::Text State_Text;
        State_Text.setString("Enter a State: ");
        State_Text.setFont(font);
        State_Text.setCharacterSize(18);
        State_Text.setFillColor(sf::Color::White);
        State_Text.setStyle(sf::Text::Bold);
        sf::FloatRect State_TextRect = Prompttext.getLocalBounds();
        State_Text.setOrigin(State_TextRect.left + State_TextRect.width / 2.0f,State_TextRect.top  + State_TextRect.height / 2.0f);
        State_Text.setPosition(window.getSize().x/2.0f - 250,window.getSize().y/2.0f - 325);

        sf::Text Min_BED;
        Min_BED.setString("Minimum number of bedrooms: ");
        Min_BED.setFont(font);
        Min_BED.setCharacterSize(18);
        Min_BED.setFillColor(sf::Color::White);
        Min_BED.setStyle(sf::Text::Bold);
        sf::FloatRect MMin_BEDRect = Min_BED.getLocalBounds();
        Min_BED.setOrigin(MMin_BEDRect.left + MMin_BEDRect.width / 2.0f,MMin_BEDRect.top  + MMin_BEDRect.height / 2.0f);
        Min_BED.setPosition(window.getSize().x/2.0f - 393,window.getSize().y/2.0f - 300);

        sf::Text Max_BED;
        Max_BED.setString("Maximum number of bedrooms: ");
        Max_BED.setFont(font);
        Max_BED.setCharacterSize(18);
        Max_BED.setFillColor(sf::Color::White);
        Max_BED.setStyle(sf::Text::Bold);
        sf::FloatRect Max_BEDRect = Min_BED.getLocalBounds();
        Max_BED.setOrigin(Max_BEDRect.left + Max_BEDRect.width / 2.0f,Max_BEDRect.top  + Max_BEDRect.height / 2.0f);
        Max_BED.setPosition(window.getSize().x/2.0f - 393,window.getSize().y/2.0f - 275);

        sf::Text Min_BATH;
        Min_BATH.setString("Minimum number of bathrooms: ");
        Min_BATH.setFont(font);
        Min_BATH.setCharacterSize(18);
        Min_BATH.setFillColor(sf::Color::White);
        Min_BATH.setStyle(sf::Text::Bold);
        sf::FloatRect Min_BATHRect = Min_BED.getLocalBounds();
        Min_BATH.setOrigin(Min_BATHRect.left + Min_BATHRect.width / 2.0f,Min_BATHRect.top  + Min_BATHRect.height / 2.0f);
        Min_BATH.setPosition(window.getSize().x/2.0f - 393,window.getSize().y/2.0f - 250);

        sf::Text Max_BATH;
        Max_BATH.setString("Maximum number of bathrooms: ");
        Max_BATH.setFont(font);
        Max_BATH.setCharacterSize(18);
        Max_BATH.setFillColor(sf::Color::White);
        Max_BATH.setStyle(sf::Text::Bold);
        sf::FloatRect Max_BATHRect = Min_BED.getLocalBounds();
        Max_BATH.setOrigin(Max_BATHRect.left + Max_BATHRect.width / 2.0f,Max_BATHRect.top  + Max_BATHRect.height / 2.0f);
        Max_BATH.setPosition(window.getSize().x/2.0f - 393,window.getSize().y/2.0f - 225);

        sf::Text Min_ACRES;
        Min_ACRES.setString("Minimum acreage: ");
        Min_ACRES.setFont(font);
        Min_ACRES.setCharacterSize(18);
        Min_ACRES.setFillColor(sf::Color::White);
        Min_ACRES.setStyle(sf::Text::Bold);
        sf::FloatRect Min_ACRESRect = Min_BED.getLocalBounds();
        Min_ACRES.setOrigin(Min_ACRESRect.left + Min_ACRESRect.width / 2.0f,Min_ACRESRect.top  + Min_ACRESRect.height / 2.0f);
        Min_ACRES.setPosition(window.getSize().x/2.0f - 393,window.getSize().y/2.0f - 200);

        sf::Text Max_ACRES;
        Max_ACRES.setString("Maximum acreage: ");
        Max_ACRES.setFont(font);
        Max_ACRES.setCharacterSize(18);
        Max_ACRES.setFillColor(sf::Color::White);
        Max_ACRES.setStyle(sf::Text::Bold);
        sf::FloatRect Max_ACRESRect = Min_BED.getLocalBounds();
        Max_ACRES.setOrigin(Max_ACRESRect.left + Max_ACRESRect.width / 2.0f,Max_ACRESRect.top  + Max_ACRESRect.height / 2.0f);
        Max_ACRES.setPosition(window.getSize().x/2.0f - 393,window.getSize().y/2.0f - 175);

        sf::Text HOME_MIN_SIZE_W;
        HOME_MIN_SIZE_W.setString("Minimum square footage of house (In Square feet): ");
        HOME_MIN_SIZE_W.setFont(font);
        HOME_MIN_SIZE_W.setCharacterSize(18);
        HOME_MIN_SIZE_W.setFillColor(sf::Color::White);
        HOME_MIN_SIZE_W.setStyle(sf::Text::Bold);
        sf::FloatRect HOME_MIN_SIZE_WRect = Min_BED.getLocalBounds();
        HOME_MIN_SIZE_W.setOrigin(HOME_MIN_SIZE_WRect.left + HOME_MIN_SIZE_WRect.width / 2.0f,HOME_MIN_SIZE_WRect.top  + HOME_MIN_SIZE_WRect.height / 2.0f);
        HOME_MIN_SIZE_W.setPosition(window.getSize().x/2.0f - 393,window.getSize().y/2.0f - 150);

        sf::Text HOME_Max_SIZE_W;
        HOME_Max_SIZE_W.setString("Maximum square footage of house (In Square feet): ");
        HOME_Max_SIZE_W.setFont(font);
        HOME_Max_SIZE_W.setCharacterSize(18);
        HOME_Max_SIZE_W.setFillColor(sf::Color::White);
        HOME_Max_SIZE_W.setStyle(sf::Text::Bold);
        sf::FloatRect HOME_Max_SIZE_WRect = Min_BED.getLocalBounds();
        HOME_Max_SIZE_W.setOrigin(HOME_Max_SIZE_WRect.left + HOME_Max_SIZE_WRect.width / 2.0f,HOME_Max_SIZE_WRect.top  + HOME_Max_SIZE_WRect.height / 2.0f);
        HOME_Max_SIZE_W.setPosition(window.getSize().x/2.0f - 393,window.getSize().y/2.0f - 125);

        sf::Text MAX_PRICE_W;
        MAX_PRICE_W.setString("Maximum price(USD): ");
        MAX_PRICE_W.setFont(font);
        MAX_PRICE_W.setCharacterSize(18);
        MAX_PRICE_W.setFillColor(sf::Color::White);
        MAX_PRICE_W.setStyle(sf::Text::Bold);
        sf::FloatRect MAX_PRICE_WRect = Min_BED.getLocalBounds();
        MAX_PRICE_W.setOrigin(MAX_PRICE_WRect.left + MAX_PRICE_WRect.width / 2.0f,MAX_PRICE_WRect.top  + MAX_PRICE_WRect.height / 2.0f);
        MAX_PRICE_W.setPosition(window.getSize().x/2.0f - 393,window.getSize().y/2.0f - 100);

        sf::Text BedROOM_IMPORTANCE_W;
        BedROOM_IMPORTANCE_W.setString("How important is having more bedrooms? (Enter a number 1-10): ");
        BedROOM_IMPORTANCE_W.setFont(font);
        BedROOM_IMPORTANCE_W.setCharacterSize(18);
        BedROOM_IMPORTANCE_W.setFillColor(sf::Color::White);
        BedROOM_IMPORTANCE_W.setStyle(sf::Text::Bold);
        sf::FloatRect BedROOM_IMPORTANCE_WRect = Min_BED.getLocalBounds();
        BedROOM_IMPORTANCE_W.setOrigin(BedROOM_IMPORTANCE_WRect.left + BedROOM_IMPORTANCE_WRect.width / 2.0f,BedROOM_IMPORTANCE_WRect.top  + BedROOM_IMPORTANCE_WRect.height / 2.0f);
        BedROOM_IMPORTANCE_W.setPosition(window.getSize().x/2.0f - 393,window.getSize().y/2.0f - 75);

        sf::Text Bathroom_IMPORTANCE_W;
        Bathroom_IMPORTANCE_W.setString("How important is having more bathrooms? (Enter a number 1-10): ");
        Bathroom_IMPORTANCE_W.setFont(font);
        Bathroom_IMPORTANCE_W.setCharacterSize(18);
        Bathroom_IMPORTANCE_W.setFillColor(sf::Color::White);
        Bathroom_IMPORTANCE_W.setStyle(sf::Text::Bold);
        sf::FloatRect Bathroom_IMPORTANCE_WRect = Min_BED.getLocalBounds();
        Bathroom_IMPORTANCE_W.setOrigin(Bathroom_IMPORTANCE_WRect.left + Bathroom_IMPORTANCE_WRect.width / 2.0f,Bathroom_IMPORTANCE_WRect.top  + Bathroom_IMPORTANCE_WRect.height / 2.0f);
        Bathroom_IMPORTANCE_W.setPosition(window.getSize().x/2.0f - 393,window.getSize().y/2.0f - 50);

        sf::Text Acre_IMPORTANCE_W;
        Acre_IMPORTANCE_W.setString("How important is having more acres? (Enter a number 1-10): ");
        Acre_IMPORTANCE_W.setFont(font);
        Acre_IMPORTANCE_W.setCharacterSize(18);
        Acre_IMPORTANCE_W.setFillColor(sf::Color::White);
        Acre_IMPORTANCE_W.setStyle(sf::Text::Bold);
        sf::FloatRect Acre_IMPORTANCE_WRect = Min_BED.getLocalBounds();
        Acre_IMPORTANCE_W.setOrigin(Acre_IMPORTANCE_WRect.left + Acre_IMPORTANCE_WRect.width / 2.0f,Acre_IMPORTANCE_WRect.top  + Acre_IMPORTANCE_WRect.height / 2.0f);
        Acre_IMPORTANCE_W.setPosition(window.getSize().x/2.0f - 393,window.getSize().y/2.0f - 25);

        sf::Text HOME_IMPORTANCE_W;
        HOME_IMPORTANCE_W.setString("How important is having a larger home size (In square foot)? (Enter a number 1-10): ");
        HOME_IMPORTANCE_W.setFont(font);
        HOME_IMPORTANCE_W.setCharacterSize(18);
        HOME_IMPORTANCE_W.setFillColor(sf::Color::White);
        HOME_IMPORTANCE_W.setStyle(sf::Text::Bold);
        sf::FloatRect HOME_IMPORTANCE_WRect = Min_BED.getLocalBounds();
        HOME_IMPORTANCE_W.setOrigin(HOME_IMPORTANCE_WRect.left + HOME_IMPORTANCE_WRect.width / 2.0f,HOME_IMPORTANCE_WRect.top  + HOME_IMPORTANCE_WRect.height / 2.0f);
        HOME_IMPORTANCE_W.setPosition(window.getSize().x/2.0f - 393,window.getSize().y/2.0f);

        sf::Text Price_IMPORTANCE_W;
        Price_IMPORTANCE_W.setString("How important is having a lower price? (Enter a number 1-10): ");
        Price_IMPORTANCE_W.setFont(font);
        Price_IMPORTANCE_W.setCharacterSize(18);
        Price_IMPORTANCE_W.setFillColor(sf::Color::White);
        Price_IMPORTANCE_W.setStyle(sf::Text::Bold);
        sf::FloatRect Price_IMPORTANCE_WRect = Min_BED.getLocalBounds();
        Price_IMPORTANCE_W.setOrigin(Price_IMPORTANCE_WRect.left + Price_IMPORTANCE_WRect.width / 2.0f,Price_IMPORTANCE_WRect.top  + Price_IMPORTANCE_WRect.height / 2.0f);
        Price_IMPORTANCE_W.setPosition(window.getSize().x/2.0f - 393,window.getSize().y/2.0f + 25);

        sf::Texture Reset_Button;
        Reset_Button.loadFromFile("Files/Images/HOMERESET_B.png");
        sf::Sprite Reset_Button_image(Reset_Button);
        sf::FloatRect Reset_Button_Bounds = Reset_Button_image.getLocalBounds();
        Reset_Button_image.setOrigin(Reset_Button_Bounds.left + Reset_Button_Bounds.width / 2.0f,Reset_Button_Bounds.top  + Reset_Button_Bounds.height / 2.0f);
        Reset_Button_image.setPosition(window.getSize().x/2.0f,window.getSize().y/2.0f + 350);

        string currentString;
        static const regex tester("^[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?$");
        static const regex importance_tester("^(10|[1-9])$");


        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::MouseButtonPressed){
                    if (event.key.code == sf::Mouse::Left) {
                        sf::Vector2i pos = sf::Mouse::getPosition(window);
                        if (Reset_Button_image.getGlobalBounds().contains(static_cast<float>(pos.x), static_cast<float>(pos.y))){
                            reset();
                            currentString = "";
                            State_Text.setString("Enter a State: ");
                        }
                    }
                }
                if (event.type == sf::Event::TextEntered){
                    if (event.text.unicode == 8 && currentString.length() != 0) {
                        // Backspace: remove the last character
                        currentString.pop_back();
                    }
                    else if (event.text.unicode < 128 && event.text.unicode != '\b' && event.text.unicode != '\n') {
                        // ASCII characters: append to the input text
                        if(currentString.length() < 16){
                            currentString += static_cast<char>(event.text.unicode);
                        }
                    }
                    if(valid_state == false){
                        State_Text.setString("Enter a State: " + currentString);
                    }
                    else if(valid_bed_min == false){
                        Min_BED.setString("Minimum number of bedrooms: " + currentString);
                    }
                    else if(valid_bed_max == false){
                        Max_BED.setString("Maximum number of bedrooms: " + currentString);
                    }
                    else if(valid_bath_min == false){
                        Min_BATH.setString("Minimum number of bathrooms: " + currentString);
                    }
                    else if(valid_bath_max == false){
                        Max_BATH.setString("Maximum number of bathrooms: " + currentString);
                    }
                    else if(valid_acre_min == false){
                        Min_ACRES.setString("Minimum acreage: " + currentString);
                    }
                    else if(valid_acre_max == false){
                        Max_ACRES.setString("Maximum acreage: " + currentString);
                    }
                    else if(valid_homesize_min == false){
                        HOME_MIN_SIZE_W.setString("Minimum square footage of house (In Square feet): " + currentString);
                    }
                    else if(valid_homesize_max == false){
                        HOME_Max_SIZE_W.setString("Maximum square footage of house (In Square feet): " + currentString);
                    }
                    else if(valid_max_price == false){
                        MAX_PRICE_W.setString("Maximum price(USD): " + currentString);
                    }
                    else if(valid_bed_importance == false){
                        BedROOM_IMPORTANCE_W.setString("How important is having more bedrooms? (Enter a number 1-10): " + currentString);
                    }
                    else if(valid_bathroom_importance == false){
                        Bathroom_IMPORTANCE_W.setString("How important is having more bathrooms? (Enter a number 1-10): " + currentString);
                    }
                    else if(valid_acre_importance == false){
                        Acre_IMPORTANCE_W.setString("How important is having more acres? (Enter a number 1-10): " + currentString);
                    }
                    else if(valid_homesize_importance == false){
                        HOME_IMPORTANCE_W.setString("How important is having a larger home size (In square foot)? (Enter a number 1-10): " + currentString);
                    }
                    else if(valid_price_importance == false){
                        Price_IMPORTANCE_W.setString("How important is having a lower price? (Enter a number 1-10): " + currentString);
                    }
                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                    // Enter key: add the current line to the vector and clear the input text
                    if(valid_state == false){
                        if(currentString == "Pennsylvania" || currentString == "New Jersey" || currentString == "New York"){
                            State = currentString;
                            currentString = "";
                            valid_state = true;
                        }
                        else{
                            currentString = "Invalid Input";
                        }
                    }
                    else if(valid_bed_min == false){
                        if(regex_match(currentString, tester) == true){
                            bed_min = stoi(currentString);
                            currentString = "";
                            valid_bed_min = true;
                        }
                        else{
                            currentString = "Invalid Input";
                        }
                    }
                    else if(valid_bed_max == false){
                        if(regex_match(currentString, tester) == true){
                            if(stoi(currentString) >= bed_min){
                                bed_max = stoi(currentString);
                                currentString = "";
                                valid_bed_max = true;
                            }
                            else{
                                currentString = "Max has to be > or = Min";
                            }
                        }
                        else{
                            currentString = "Invalid Input";
                        }
                    }
                    else if(valid_bath_min == false){
                        if(regex_match(currentString, tester) == true){
                            bathroom_min = stod(currentString);
                            currentString = "";
                            valid_bath_min = true;
                        }
                        else{
                            currentString = "Invalid Input";
                        }
                    }
                    else if(valid_bath_max == false){
                        if(regex_match(currentString, tester) == true){
                            if(stod(currentString) >= bathroom_min){
                                bathroom_max = stod(currentString);
                                currentString = "";
                                valid_bath_max = true;
                            }
                            else{
                                currentString = "Max has to be > or = Min";
                            }
                        }
                        else{
                            currentString = "Invalid Input";
                        }
                    }
                    else if(valid_acre_min == false){
                        if(regex_match(currentString, tester) == true){
                            min_acres = stod(currentString);
                            currentString = "";
                            valid_acre_min = true;
                        }
                        else{
                            currentString = "Invalid Input";
                        }
                    }
                    else if(valid_acre_max == false){
                        if(regex_match(currentString, tester) == true){
                            if(stod(currentString) >= min_acres){
                                max_acres = stod(currentString);
                                currentString = "";
                                valid_acre_max = true;
                            }
                            else{
                                currentString = "Max has to be > or = Min";
                            }
                        }
                        else{
                            currentString = "Invalid Input";
                        }
                    }
                    else if(valid_homesize_min == false){
                        if(regex_match(currentString, tester) == true){
                            min_homesize = stoi(currentString);
                            currentString = "";
                            valid_homesize_min = true;
                        }
                        else{
                            currentString = "Invalid Input";
                        }
                    }
                    else if(valid_homesize_max == false){
                        if(regex_match(currentString, tester) == true){
                            if(stod(currentString) >= min_homesize){
                                max_homesize = stoi(currentString);
                                currentString = "";
                                valid_homesize_max = true;
                            }
                            else{
                                currentString = "Max has to be > or = Min";
                            }
                        }
                        else{
                            currentString = "Invalid Input";
                        }
                    }
                    else if(valid_max_price == false){
                        if(regex_match(currentString, tester) == true){
                            max_price = stoi(currentString);
                            currentString = "";
                            valid_max_price = true;
                        }
                        else{
                            currentString = "Invalid Input";
                        }
                    }
                    else if(valid_bed_importance == false){
                        if(regex_match(currentString, importance_tester) == true){
                            bed_importance = stoi(currentString);
                            currentString = "";
                            valid_bed_importance = true;
                        }
                        else{
                            currentString = "Invalid Input";
                        }
                    }
                    else if(valid_bathroom_importance == false){
                        if(regex_match(currentString, importance_tester) == true){
                            bathroom_importance = stoi(currentString);
                            currentString = "";
                            valid_bathroom_importance = true;
                        }
                        else{
                            currentString = "Invalid Input";
                        }
                    }
                    else if(valid_acre_importance == false){
                        if(regex_match(currentString, importance_tester) == true){
                            acre_importance = stoi(currentString);
                            currentString = "";
                            valid_acre_importance = true;
                        }
                        else{
                            currentString = "Invalid Input";
                        }
                    }
                    else if(valid_homesize_importance == false){
                        if(regex_match(currentString, importance_tester) == true){
                            homesize_Importance = stoi(currentString);
                            currentString = "";
                            valid_homesize_importance = true;
                        }
                        else{
                            currentString = "Invalid Input";
                        }
                    }
                    else if(valid_price_importance == false){
                        if(regex_match(currentString, importance_tester) == true){
                            price_importance = stoi(currentString);
                            currentString = "";
                            valid_price_importance = true;
                        }
                        else{
                            currentString = "Invalid Input";
                        }
                    }
                }
            }

            window.clear();
            window.draw(rect);
            window.draw(Title);
            window.draw(Prompttext);
            window.draw(State_Text);
            if(valid_state == true){
                window.draw(Min_BED);
            }
            if(valid_bed_min == true){
                window.draw(Max_BED);
            }
            if(valid_bed_max == true){
                window.draw(Min_BATH);
            }
            if(valid_bath_min == true){
                window.draw(Max_BATH);
            }
            if(valid_bath_max == true){
                window.draw(Min_ACRES);
            }
            if(valid_acre_min == true){
                window.draw(Max_ACRES);
            }
            if(valid_acre_max == true){
                window.draw(HOME_MIN_SIZE_W);
            }
            if(valid_homesize_min == true){
                window.draw(HOME_Max_SIZE_W);
            }
            if(valid_homesize_max == true){
                window.draw(MAX_PRICE_W);
            }
            if(valid_max_price == true){
                window.draw(BedROOM_IMPORTANCE_W);
            }
            if(valid_bed_importance == true){
                window.draw(Bathroom_IMPORTANCE_W);
            }
            if(valid_bathroom_importance == true){
                window.draw(Acre_IMPORTANCE_W);
            }
            if(valid_acre_importance == true){
                window.draw(HOME_IMPORTANCE_W);
            }
            if(valid_homesize_importance == true){
                window.draw(Price_IMPORTANCE_W);
            }
            // Draw your graphics here
            window.draw(Reset_Button_image);
            window.display();
            if(valid_price_importance == true){
                window.close();
                results();
            }
        }
    }

    vector<string> quicksort()
    //function that places dataset in vector then calls quick sort function
    //While also keeping track of time it take for quicksort to occur
    {
        vector<string> houses;
        for (auto itr = dataset.begin(); itr != dataset.end(); itr++) {
            houses.push_back(itr->first);
        }
        if (houses.size() <= 1) //not enough houses to sort
        {
            time_quick = 0;
            quick_rankings = houses;
        } else {
            auto start_time = chrono::high_resolution_clock::now();
            quicksort_helper(houses, 0, houses.size() - 1);
            auto end_time = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
            time_quick = duration;
            quick_rankings = houses;
        }
        return houses;
    }

    void quicksort_helper(vector<string> &houses, int left, int right)
    //function that recusivly call quicksort_helper until left value is less than right ie: sorted
    {
        if (left < right) {
            int p = partition(houses, left, right);
            quicksort_helper(houses, left, p - 1); //sort left of pivot
            quicksort_helper(houses, p + 1, right); //sort right of pivot
        }
    }

    int partition(vector<string> &houses, int left, int right)
    //function that takes vectors and swaps houses based off value compare to pivot
    {
        string pivot = houses[left]; //set pivot to the first element of the vector
        int up = left;
        int down = right;
        while (up < down) //sort around the pivot
        {
            while (up < right && stoi(dataset[houses[up]][0]) >= stoi(dataset[pivot][0])) {
                up++;
            }
            while (down > left && stoi(dataset[houses[down]][0]) <= stoi(dataset[pivot][0])) {
                down--;
            }
            if (up < down) {
                swap(houses, up, down);
            }
        }
        swap(houses, left, down);
        return down;
    }

    void swap(vector<string> &houses, int left, int right)
    //Swaps the postion of the houses at left and right index
    {
        string temp = houses[right];
        houses[right] = houses[left];
        houses[left] = temp;
    }


    vector<string> MergeSort()
    //function that places values in a vector then call merge sort for that vector.
    // While also taking the time for merge sort function to occur
    {
        for (auto it = dataset.begin(); it != dataset.end(); ++it) {
            merge_sort_vector.push_back(it->first);
        }

        if (merge_sort_vector.size() <= 1) //not enough houses to sort
        {
            time_merge = 0;
            merge_rankings = merge_sort_vector;
        } else {
            auto start_time = chrono::high_resolution_clock::now();
            MergeSortFunction(dataset, merge_sort_vector, 0, merge_sort_vector.size() - 1);
            auto end_time = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
            time_merge = duration;
        }
        merge_rankings = merge_sort_vector;
        return merge_rankings;
    }

    void MergeSortFunction(unordered_map<string, vector<string>> &DataSetMap, vector<string> &DataSetVector, int left,
                           int right)
    //function that recusively  call mergesort until left value is less than right ie: sorted
    {
        if (left < right) {
            int mid = left + (right - left) / 2;

            MergeSortFunction(DataSetMap, DataSetVector, left, mid);
            MergeSortFunction(DataSetMap, DataSetVector, mid + 1, right);

            HelperMerge(DataSetMap, DataSetVector, left, mid, right);
        }
    }

    void
    HelperMerge(unordered_map<string, vector<string>> &DataSetMap, vector<string> &Houses, int left, int mid, int right)
    //Function that performs the merge sort by comparing values and moving location of data based off of comparison
    {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        vector<string> leftVect(Houses.begin() + left, Houses.begin() + left + n1);
        vector<string> rightVect(Houses.begin() + mid + 1, Houses.begin() + mid + 1 + n2);

        int i = 0;
        int j = 0;
        int k = left;

        while (i < n1 && j < n2) {
            if (compareHouses(DataSetMap, leftVect[i], rightVect[j])) {
                Houses[k++] = leftVect[i++];
            } else {
                Houses[k++] = rightVect[j++];
            }
        }

        while (i < n1) {
            Houses[k++] = leftVect[i++];
        }

        while (j < n2) {
            Houses[k++] = rightVect[j++];
        }


    }

    bool compareHouses(unordered_map<string, vector<string>> &DataSetMap, string &house1, string &house2)
    //function to compare houses first based off score then based off price if scores are equal
    {

        int score1value;
        int score2value;
        int price1value;
        int price2value;

        string score1 = DataSetMap[house1][0];
        score1value = stoi(score1);
        string price1 = DataSetMap[house1][1];;
        price1value = stoi(price1);

        string score2 = DataSetMap[house2][0];
        score2value = stoi(score2);
        string price2 = DataSetMap[house2][1];;
        price2value = stoi(price2);


        if (score1value > score2value) {
            return true;
        } else if (score1value < score2value) {
            return false;
        } else {
            if (price1value < price2value) {
                return true;
            } else {
                return false;
            }
        }
    }

    bool compare_results()
    //function to checks if the results from merge and quick sort are the same
    {
        for (int i = 0; i < 3; i++) {
            if (stoi(dataset[merge_rankings[i]][0]) != stoi(dataset[quick_rankings[i]][0])) {
                return false;
            } else if (stoi(dataset[merge_rankings[i]][1]) != stoi(dataset[quick_rankings[i]][1])) {
                return false;
            } else {
                return true;
            }
        }
    }

};

int main(){
    Homes_Sorter T;
    T.main_screen();
    return 0;
}
