#include <QApplication>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QHeaderView>

class PharmacySearch : public QWidget {

public:
    PharmacySearch(QWidget *parent = nullptr) : QWidget(parent) {
        setWindowTitle("Pharmacy Search");

        // Title
        auto title = new QLabel("Pharmacy Search", this);
        title->setStyleSheet("font: 16pt Arial;");
        title->setAlignment(Qt::AlignCenter);

        // Explanation
        auto explanation = new QLabel("This is a Search to find Catalan pharmacies from their postal code", this);
        explanation->setAlignment(Qt::AlignCenter);

        // label
        auto label = new QLabel("Postal Code:", this);

        // entry
        entry = new QLineEdit(this);

        // search button
        auto searchButton = new QPushButton("Search", this);
        connect(searchButton, &QPushButton::clicked, this, &PharmacySearch::search);

        // table
        table = new QTableWidget(this);
        table->setColumnCount(9);
        table->setHorizontalHeaderLabels({"No", "Pharmacy Name", "Postal Code", "ABS Code", "ABS Name", "Type of Street", "Street Name", "Street Number", "Municipality"});
        table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        table->setEditTriggers(QAbstractItemView::NoEditTriggers);

        // layout
        auto mainLayout = new QVBoxLayout(this);
        mainLayout->addWidget(titlemainLayout->addWidget(explanation);
        mainLayout->addWidget(label);
        mainLayout->addWidget(entry);
        mainLayout->addWidget(searchButton);
        mainLayout->addWidget(table);

        setLayout(mainLayout);
    }

private:
    void search() {
        QString postalCode = entry->text();
        QNetworkAccessManager *manager = new QNetworkAccessManager(this);
        connect(manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply) {
            if (reply->error()) {
                throw std::runtime_error(QString("Error while fetching data: %1").arg(reply->errorString()).toStdString());
            } else {
                QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
                QJsonArray array = document.array();
                for (int i = 0; i < array.size(); ++i) {
                    QJsonObject obj = array.at(i).toObject();
                    if (obj["CODI POSTAL"].toString() == postalCode) {
                        int row = table->rowCount();
                        table->insertRow(row);
                        table->setItem(row, 0, new QTableWidgetItem(QString::number(row + 1)));
                        table->setItem(row, 1, new QTableWidgetItem(obj["NOM FARMACIA"].toString()));
                        table->setItem(row, 2, new QTableWidgetItem(obj["CODI POSTAL"].toString()));
                        table->setItem(row, 3, new QTableWidgetItem(obj["CODI ABS"].toString()));
                        table->setItem(row, 4, new QTableWidgetItem(obj["NOM ABS"].toString()));
                        table->setItem(row, 5, new QTableWidgetItem(obj["TIPUS VIA"].toString()));
                        table->setItem(row, 6, new QTableWidgetItem(obj["NOM VIA"].toString()));
                        table->setItem(row, 7, new QTableWidgetItem(obj["NUMERO VIA"].toString()));
                        table->setItem(row, 8, new QTableWidgetItem(obj["NOM MUNICIPI"].toString()));
                    }
                }
        });
        manager->get(QNetworkRequest(QUrl("https://pompeu.neocities.org/farmacies/farmacies.json")));
    }

    QLineEdit *entry;
    QTableWidget *table;
};

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    PharmacySearch w;
    w.show();
    return a.exec();
}

