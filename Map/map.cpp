#include "map.h"

Map::Map(const int size, const QRectF rect, const vector<string> cities) : _cities(){
    _rect = rect;
    //Generation(size, cities);
}

void Map::Generation(const int size, const vector<string> cities){

    _cities.clear();

    for(int i = 0; i < size; ++i){ shared_ptr<City> city = std::make_shared<City>();
        if(cities.empty()){
            city->name = std::to_string(i);
        }else{
            city->name = cities[i % cities.size()];
        }

        city->coordinates.x = rand() % ((int)_rect.width() - 40) + 20;
        city->coordinates.y = rand() % ((int)_rect.height() - 40) + 20;
        city->id = i;

        _cities.push_back(city);
    }

}

void Map::SetRect(const QRect rect){
    _rect = rect;
}

City Map::GetCity(const int id) const{
    if(_cities[id]->id == id){
        return *_cities[id];
    }

    for(auto city : _cities){
        if(city->id == id){
            return *city;
        }
    }

    return City();
}

/*
 *auto Map::begin() const -> decltype(_cities.begin()){
 *    return _cities.begin();
 *}
 *
 *auto Map::end() const -> decltype(_cities.end()){
 *    return _cities.end();
 *}
 */

/*
 *void Map::Edit(const int number, const City city){
 *    _cities[number] = city;
 *}
 */
void Map::SetBeginCity(const int index){
    _cities[_beginCity]->isBegin = false;
    _cities[index]->isBegin = true;
    _beginCity = index;
}

int Map::GetSize() const{
    return _cities.size();
}

int Map::CalcLength(const vector<int> ways, const int numberBeginCity) const{

    if(ways.size() <= 1){
        return 0;
    }

    City beginCity = *_cities[numberBeginCity];
    City prevCity = beginCity;
    int sum = 0;
    int sizeWays = ways.size();
    for(int i = 0; i < sizeWays; ++i){
        int w = ways[i];
        City currCity = *_cities[w];

        Point p1, p2;
        p1.x = prevCity.coordinates.x;
        p1.y = prevCity.coordinates.y;

        p2.x = currCity.coordinates.x;
        p2.y = currCity.coordinates.y;

        sum += MathTwoPoint::CalcDistance(p1, p2);

        prevCity = currCity;
    }
    Point p1, p2;
    p1.x = beginCity.coordinates.x;
    p1.y = beginCity.coordinates.y;

    p2.x = prevCity.coordinates.x;
    p2.y = prevCity.coordinates.y;

    sum += MathTwoPoint::CalcDistance(p1, p2);

    return sum;
}
