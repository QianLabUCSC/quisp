/** \file Clause.h
 *  \authors cldurand
 *  \date 2018/07/03
 *
 *  \brief Clause
 */
#ifndef QUISP_RULES_CLAUSE_H_
#define QUISP_RULES_CLAUSE_H_

#include <omnetpp.h>
#include <modules/QNIC.h>
#include <modules/QUBIT.h>

using namespace quisp::modules;

namespace quisp {
namespace rules {

/** \class Clause Clause.h
 *
 *  \brief Clause
 */
class Clause {
    protected:
        int partner; /**< Identifies entanglement partner. */
        QNIC_type qnic_type;
        int qnic_id;
        int resource; /**< Identifies qubit */

    public:
        Clause(int partner, int resource) : Clause(partner, QNIC_N, -1, resource) {};
        Clause(int part, QNIC_type qt, int qi, int res) {
            partner = part;
            qnic_type = qt;
            qnic_id = qi;
            resource = res;
        };
        void setQnic(QNIC_type qt, int qi) {
            //if (qt >= QNIC_N) omnetpp::error("Not that many QNIC types.");
            //if (qi < 0) omnetpp::error("Negative qnic index.");
            qnic_type = qt;
            qnic_id = qi;
        };
        void checkQnic() const {
            //if (qnic_type >= QNIC_N) omnetpp::error("Not that many QNIC types.");
            //if (qnic_id < 0) omnetpp::error("Negative qnic index.");
        };
        virtual int check(qnicResources *resources) const = 0;
};

class FidelityClause : public Clause {
    protected:
        double threshold;

    public:
        FidelityClause(int partner, int resource, double fidelity) : Clause(partner, resource) {
            threshold = fidelity;
        };
        int check(qnicResources *resources) const override;
};

class XErrClause : public Clause {};

} // namespace rules
} // namespace quisp

#endif//QUISP_RULES_CLAUSE_H_