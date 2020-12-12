#include "connection.h"
#include "metodes.h"

connection::connection()
{

}

void connection::connectToDataBase(){
    db = initBd();
}

//bool connection::inserIntoTable(const QVariantList &data);
//void connection::closeDb()
//{
//    QSqlQuery requeteur;
//     requeteur.exec("DELETE FROM test");
//    db.close();
//}


//void seedOnce()
//{
//    QSqlQuery requeteur;
//     requeteur.prepare("INSERT INTO test(id, name) VALUES (:newId, :newRubrique)");     // Utilisation de variable bind
//     requeteur.bindValue(":newId", 1); // Liaison entre la variable bind et la variable applicative pour l'identifiant->
//     requeteur.bindValue(":newRubrique", "nouvelleRubrique"); // Liaison entre la variable bind et la variable applicative pour le titre de la rubrique->
//     requeteur.exec();
//     requeteur.bindValue(":newId", 2);
//     requeteur.bindValue(":newRubrique", "nouvelleRubrique2");
//     requeteur.exec();

//}
