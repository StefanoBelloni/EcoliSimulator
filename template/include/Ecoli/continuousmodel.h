#ifndef CONTINUOUSMODEL_H
#define CONTINUOUSMODEL_H

namespace ecoli{

/*! \brief this class implements the continuous model of the bacterium (that is to say which PDE the density of the population satisties)
 */

class ContinuousModel
{
    public:
        /** Default constructor */
        ContinuousModel();
        /** Default destructor */
        virtual ~ContinuousModel();

    protected:

    private:
};

}
#endif // CONTINUOUSMODEL_H
