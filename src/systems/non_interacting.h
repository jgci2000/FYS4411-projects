#ifndef NON_INTERACTING_H
#define NON_INTERACTING_H

#include "system.h"

class NonInteracting : public System{
public:

    NonInteracting(int N_, int dim_, double omega_) : System(N_, dim_, omega_) {}

    long double evaluate_wf(long double *r) {
        double r2_sum = 0;
        for (int d = 0; d < dim; ++d) {
            r2_sum += SQUARE(r[d]);
        }
        
        return exp(- alpha * r2_sum);
    }

    long double gradient_component_wf(long double x) {
        return -2 * alpha * x;
    }

    void gradient_wf(long double *grad, long double *r) {
        for (int d = 0; d < dim; d++) {
            grad[d] = -2 * alpha * r[d];
        }
    }

    long double laplacian_wf(long double *r) {
        double r2_sum = 0;
        for (int d = 0; d < dim; ++d) {
            r2_sum += SQUARE(r[d]);
        }

        return 4 * SQUARE(alpha) * r2_sum - 2 * alpha * dim;
    }

    void quantum_force(long double *force, long double *r) {
        for (int d = 0; d < dim; d++) {
            force[d] = - 4 * alpha * r[d];
        }
    }

    long double local_energy() {
        double r2_sum = 0;
        for (int i = 0; i < N; ++i) {
            for (int d = 0; d < dim; ++d) {
                r2_sum += SQUARE(r[i][d]);
            }
        }

        return N * dim * alpha - 2 * SQUARE(alpha) * r2_sum + 0.5 * SQUARE(omega) * r2_sum;
    }

};

#endif // NON_INTERACTING_H
