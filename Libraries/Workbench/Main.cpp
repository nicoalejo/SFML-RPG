#include <HighscoreManager.h>
#define TOP 5

int main() {
	HighscoreManager* HSM = new HighscoreManager(TOP);
	// Se agregan scores
	HSM->AddScore("jorge", 1000);
	HSM->AddScore("ramiro", 4000);
	HSM->AddScore("CarlOs", 666);
	HSM->AddScore("Dani", 1717);
	HSM->AddScore("Sergio", 99999);
	// Se muestran scores
	HSM->ShowScores();
	// Se remueve a ramiro
	cout << "Se remueve a Ramiro" << endl;
	if (HSM->RemoveScore("raMiRo"))
		cout << "Se removio a Ramiro" << endl;
	else
		cout << "No se pudo remover a Ramiro" << endl;
	HSM->ShowScores();
	// Se remueve la segunda posicion de los scores
	cout << "Se remueve el score en segunda posicion" << endl;
	if (HSM->RemoveScore(2))
		cout << "Se removio score en posicion 2" << endl;
	else
		cout << "No se pudo remover score en posicion 2" << endl;
	HSM->ShowScores();
	// Se busca el score en posicion 1
	cout << "Se obtiene el score en la posicion 1" << endl;
	cout << "Nombre en posicion 1: " << HSM->GetScore(1)->GetName() << " y su score es: " << HSM->GetScore(1)->GetScore() << endl;
	delete HSM;
	cin.get();
}