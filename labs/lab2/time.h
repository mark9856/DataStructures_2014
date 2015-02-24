class Time{
    public:
        Time();
        Time(int aHour, int aMinute, int aSecond);

        // ACCESSORS
        int getHour() const;
        int getMinute() const;
        int getSecond() const;

        // MODIFIERS
        void setHour(int aHour);
        void setMinute(int aMinute);
        void setSecond(int aSecond);

        // OTHER MODIFIERS
        void PrintAmPm();

    private:
        int hour;
        int minute;
        int second;
        bool pm;
};

bool IsEarlierThan(const Time & t1, const Time & t2);
// bool IsEarlierThan(const Time t1, const Time t2);
