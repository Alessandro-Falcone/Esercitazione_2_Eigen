#include <iostream>
#include "Eigen/Eigen"

using namespace std;
using namespace Eigen;

// funzione che risolve il sistema lineare con la fattorizzazione PALU
VectorXd soluzioneSistemaPALU(const MatrixXd& A, const VectorXd& b){

    Vector2d xPALU = A.fullPivLu().solve(b);

    // ritorna la soluzione del sistema
    return xPALU;
}

// funzione che risolve il sistema lineare con la fattorizzazione QR
VectorXd soluzioneSistemaQR(const MatrixXd& A, const VectorXd& b){

    Vector2d xQR = A.fullPivHouseholderQr().solve(b);

    // ritorna la soluzione del sistema
    return xQR;
}

// funzione che trova la soluzione effettiva del sistema Ax = b
// ritorna l'errore relativo per la fattorizzazione PALU
// ritorna l'errore relativo per la fattorizzazione QR
void testSoluzione(const MatrixXd& A, const VectorXd& b, const VectorXd& soluzione,
                   double& errRelPALU, double& errRelQR){


    errRelPALU = numeric_limits<double>::max();
    // massimo valore che può assumere un double, assegnato all'errore relativo per la fattorizzazione PALU

    errRelQR = numeric_limits<double>::max();
    // massimo valore che può assumere un double, assegnato all'errore relativo per la fattorizzazione QR

    // soluzioneSistemaPALU(A,b)

    errRelPALU = (soluzioneSistemaPALU(A,b) - soluzione).norm() / soluzione.norm(); // errore relativo per fattorizzazione PALU

    // soluzioneSistemaQR(A,b)

    errRelQR = (soluzioneSistemaQR(A,b) - soluzione).norm() / soluzione.norm(); // errore relativo per fattorizzazione QR
}

int main(){

    Vector2d soluzione(-1.0000e+0, -1.0000e+00);
    Matrix2d A1 = Matrix2d::Zero();
    A1 << 5.547001962252291e-01, -3.770900990025203e-02, 8.320502943378437e-01, -9.992887623566787e-01;
    Vector2d b1 = Vector2d::Zero();
    b1 << -5.169911863249772e-01, 1.672384680188350e-01;

    Matrix2d A2 = Matrix2d::Zero();
    A2 << 5.547001962252291e-01, -5.540607316466765e-01, 8.320502943378437e-01, -8.324762492991313e-01;
    Vector2d b2 = Vector2d::Zero();
    b2 << -6.394645785530173e-04, 4.259549612877223e-04;

    Matrix2d A3 = Matrix2d::Zero();
    A3 << 5.547001962252291e-01, -5.547001955851905e-01, 8.320502943378437e-01, -8.320502947645361e-01;
    Vector2d b3 = Vector2d::Zero();
    b3 << -6.400391328043042e-10, 4.266924591433963e-10;

    double errRel1PALU;
    double errRel1QR;

    double errRel2PALU;
    double errRel2QR;

    double errRel3PALU;
    double errRel3QR;

    testSoluzione(A1, b1, soluzione, errRel1PALU, errRel1QR);
    testSoluzione(A2, b2, soluzione, errRel2PALU, errRel2QR);
    testSoluzione(A3, b3, soluzione, errRel3PALU, errRel3QR);

    if (errRel1PALU < 1e-15 && errRel1QR < 1e-15){ // condizione sulla tolleranza del primo sistema

        cout << scientific << "1 -> " << "errore relativo fattorizzazione PALU: " << errRel1PALU << " - errore relativo fattorizzazione QR: " << errRel1QR << endl;

    }else{
        cerr << "1-soluzione errata del primo sistema" << endl;
        return 1;
    }

    if (errRel2PALU < 1e-12 && errRel2QR < 1e-12){ // condizione sulla tolleranza del secondo sistema

        cout << scientific << "2 -> " << "errore relativo fattorizzazione PALU: " << errRel2PALU << " - errore relativo fattorizzazione QR: " << errRel2QR << endl;

    }else{
        cerr << "2-soluzione errata del secondo sistema" << endl;
        return 1;
    }

    if (errRel3PALU < 1e-5 && errRel3QR < 1e-5){ // condizione sulla tolleranza del terzo sistema

       cout << scientific << "3 -> " << "errore relativo fattorizzazione PALU: " << errRel3PALU << " - errore relativo fattorizzazione QR: " << errRel3QR << endl;

    }else{
        cerr << "3-soluzione errata del terzo sistema" << endl;
        return 1;
    }

    return 0;
}

