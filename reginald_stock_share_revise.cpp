#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

class Stock {
  public:

  string name;
  double market_price, market_value;
  int total_shares, whole_dollar, numerator, denominator;

  double get_price(int whole_dollar, int numerator, int denominator) {
    return whole_dollar + static_cast<double>(numerator) / denominator;
  }

  int get_value(string message) {
    int value;
    do {
      cout << "  " << message;
      cin >> value;
    } while (value < 1);
    return value;
  }

  void get_values(string stock_name) {
    cout << "Stock Name: " << stock_name << endl;
    name = stock_name;
    total_shares = get_value("Enter total shares: ");
    whole_dollar = get_value("Enter whole dollar price: ");
    numerator = get_value("Enter price numerator: ");
    denominator = get_value("Enter price denominator: ");
    market_price = get_price(whole_dollar, numerator, denominator);
    market_value = market_price * total_shares;
    cout << endl;
  }

  Stock(string stock_name) {
    get_values(stock_name);
  }
};

class Market {
  public:

  int column_size;
  vector<Stock> stocks;
  vector<string> headers = {"Stock Name", "Market Price", "Total Shares", "Market value"};

  void add_name(string stock_name) {
    stocks.push_back(Stock(stock_name));
  }

  void display_headers(void) {
    for (string header: headers) {
      cout << setw(column_size) << header;
    }
    cout << endl;
  }

  void display_line(void) {
    for (string header: headers) {
      for (int count=0; count < column_size; count++) {
        cout << "-";
      }
    }
    cout << endl;
  }

  void display_values(void) {
    display_line();
    display_headers();
    display_line();
    double total_trade_value = 0;
    cout << fixed << setprecision(2);
    for (Stock stock: stocks) {
      cout  << setw(column_size) << stock.name
            << setw(column_size) << stock.market_price
            << setw(column_size) << stock.total_shares
            << setw(column_size) << stock.market_value
            << endl;
      total_trade_value = total_trade_value + stock.market_value;
    }
    display_line();
    cout  << setw(column_size * 3) << "Total Trade Value"
          << setw(column_size) << total_trade_value
          << endl;
    display_line();
  }

  Market(int size) {
    column_size = size;
  }
};

bool repeat(string repeat = "") {
  while (repeat != "y" && repeat != "n") {
    cout << "Do you want to continue?(y,n) ";
    cin >> repeat;
  } return repeat == "y";
}

int main(void) {
  do {
    Market stocks(15);
    stocks.add_name("Jollibee");
    stocks.add_name("Mac Donalds");
    stocks.add_name("RJ Pizza");
    stocks.display_values();
  } while (repeat());

  return 0;
}
