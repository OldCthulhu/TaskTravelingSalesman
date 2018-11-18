#ifndef _MAP_H_
#define _MAP_H_
#include "includes.h"
#include "Math/mathq.h"

struct City{
   int id;
   string name;
   Point coordinates;
   bool isBegin = false;
};

class Map{
public:
    explicit Map(const int size, const QRectF rect, const vector<string> listCities);
    void Generation(const int size, const vector<string> listCities);
    int GetSize() const;
    int CalcLength(const vector<int> way, const int beginCity) const;

    City GetCity(const int id) const;
    void SetRect(const QRect rect);
    void SetBeginCity(const int index);

    auto begin() const{
        return _cities.begin();
    }

    auto end() const{
        return _cities.end();
    }

private:
    int _beginCity = 0;
    QRectF _rect;
    vector<shared_ptr<City>> _cities;
};

#endif
