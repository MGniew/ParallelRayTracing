#include "slavempi.h"
#include "global.h"

SlaveMPI::SlaveMPI()
{
}

int SlaveMPI::exec()
{
    //while(true)
    {

        int v[2];
        int tag;
        MPI_Status status;
        std::vector<char> vec;
        vec.resize(Vector3<float>::serializedSize);
        MPI_Recv(vec.data(), 255, MPI_BYTE, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

        Vector3<float> a;
        a.deserialize(vec);
        std::cout << a.x << " " << a.y << " " << a.z << std::endl;
        //calculations
        //send result
        MPI_Finalize();

    }


    return 0;
}
