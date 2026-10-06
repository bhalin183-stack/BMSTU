#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct Bagazh {
    string name;
    double weight;
};

struct Passazhir {
    string fio;
    vector<Bagazh> items;
};

int main() {
    int n;
    cout << "Введите число пассажиров n: ";
    if (!(cin >> n) || n <= 0) {
        cout << "Ошибка: некорректное количество пассажиров!" << endl;
        return 1;
    }

    cin.ignore();

    vector<Passazhir> passengers(n);

    for (int i = 0; i < n; i++) {
        cout << "\n=== Пассажир №" << i + 1 << " ===\n";
        cout << "ФИО пассажира: ";
        getline(cin, passengers[i].fio);

        int items_count;
        cout << "Количество предметов багажа: ";
        cin >> items_count;
        if (items_count < 0) items_count = 0;

        passengers[i].items.resize(items_count);

        for (int j = 0; j < items_count; j++) {
            cin.ignore();
            cout << " Предмет №" << j + 1 << " - Название: ";
            getline(cin, passengers[i].items[j].name);

            cout << " Предмет №" << j +1 << " - Вес (кг): ";
            cin >> passengers[i].items[j].weight;
        }

        cin.ignore();
    }

    cout << "\nСПИСОК ПАССАЖИРОВ И ИХ БАГАЖА:\n";
    for (int i = 0; i < n; i++) {
        cout << "Пассажир: " << passengers[i].fio << endl;
        if (passengers[i].items.empty()) {
            cout << " [Багаж отсутствует]\n";
        } else {
            for (size_t j = 0; j < passengers[i].items.size(); j++) {
                cout << " - " << passengers[i].items[j].name
                << ": " << passengers[i].items[j].weight << " кг\n";
            }
        }
    }
    cout << "\nРАСЧЕТ: Средний вес одного предмета багажа:\n";

    cout << fixed << setprecision(2);

    for (int i = 0; i < n; i++) {
        cout << "Пассажир: " << passengers[i].fio << endl;

        if (passengers[i].items.empty()) {
            cout << " Средний вес: 0.00 кг (нет предметов багажа)\n";
        } else {
            double total_weight = 0.0;

            for (size_t j=0; j < passengers[i].items.size(); j++) {
                total_weight += passengers[i].items[j].weight;
            }

            double average_weight = total_weight / passengers[i].items.size();

            cout << " Всего предметов: " << passengers[i].items.size()
                 << " | Общий вес: " << total_weight << " кг\n";
            cout << " Средний вес одного предмета: " << average_weight << " кг\n";
        }
    }

    return 0;
}