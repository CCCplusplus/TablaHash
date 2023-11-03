class HashItem {
private:
    std::string key;
    int value; // La frecuencia de la palabra
    bool isEmpty;

public:
    HashItem() : key(""), value(0), isEmpty(true) {}

    void setKey(const std::string& k) {
        key = k;
        isEmpty = false;
    }

    void setValue(int v) { value = v; }

    std::string getKey() const { return key; }

    int getValue() const { return value; }

    void incrementValue() { value++; }

    bool empty() const { return isEmpty; }

    void clear() {
        key = "";
        value = 0;
        isEmpty = true;
    }
};
