class Time{
    public:
        Time();
        Time(uintptr_t aHour, uintptr_t aMinute, uintptr_t aSecond);

        // ACCESSORS
        uintptr_t getHour() const;
        uintptr_t getMinute() const;
        uintptr_t getSecond() const;

        // MODIFIERS
        void setHour(uintptr_t aHour);
        void setMinute(uintptr_t aMinute);
        void setSecond(uintptr_t aSecond);

        // OTHER MODIFIERS
        void PrintAmPm();

    private:
        uintptr_t hour;
        uintptr_t minute;
        uintptr_t second;
        bool pm;
};

bool IsEarlierThan(const Time & t1, const Time & t2);
// bool IsEarlierThan(const Time t1, const Time t2);
