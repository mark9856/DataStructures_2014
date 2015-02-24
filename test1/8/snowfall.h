#include <iostream>
#include <vector>

class Snowfall{
    public:
        // CONSTRUCTOR
        Snowfall(std::string cityName, int durationHour, float snowAmount);

        // ACCESSOR
        std::string getCityName() const;
        float getTotal() const;

        // OTHER MODIFITOR
        void setSnowInHour(int sHour, float snowAmount);

    private:
        std::string city;
        int duration;
        std::vector <double> snows;
};

bool by_total_snowfall(const Snowfall s1, const Snowfall s2);
