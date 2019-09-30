#include "janibekovsBolt.h"
#include <core/fileformats/meshLoader.h>
JanibekovsBolt::JanibekovsBolt(double arm, double mass)
{
    setSystemMass(mass);
    double massOfRotatingObjects = 6;
    double massOfTestingObject = 1;
    double massOfZeroObject = 0.0;
    double partsRadius = 0.01;
    Affine3DQ defaultPos = Affine3DQ(Vector3dd::Zero());

    partsOfSystem.push_back(PhysSphere(&defaultPos, &partsRadius, &massOfRotatingObjects));
    partsOfSystem.push_back(PhysSphere(&defaultPos, &partsRadius, &massOfRotatingObjects));
    partsOfSystem.push_back(PhysSphere(&defaultPos, &partsRadius, &massOfTestingObject));
    partsOfSystem.push_back(PhysSphere(&defaultPos, &partsRadius, &massOfZeroObject));

    partsOfSystem[0].color = RGBColor::Red();    /*Front right*/
    partsOfSystem[1].color = RGBColor::Red();  /*Back  left*/
    partsOfSystem[2].color = RGBColor::Green();    /*Front left*/
    partsOfSystem[3].color = RGBColor::Yellow();  /*Back  right*/

    partsOfSystem[0].setPos(Vector3dd( 0,  1, 0).normalised() * 3 * arm);
    partsOfSystem[1].setPos(Vector3dd( 0, -1, 0).normalised() * 3 * arm);
    partsOfSystem[2].setPos(Vector3dd( 1,  0, 0).normalised() * arm);
    partsOfSystem[3].setPos(Vector3dd(-1,  0, 0).normalised() * arm);

    MeshLoader loader;
    Mesh3DDecorated mesh;
    if (loader.load(&mesh, "models/OBJ.obj"))
    {
        /* mm -> m and shift to right position */
        worldMesh = new Mesh3DDecorated;
        mesh.transform(Matrix44::RotationZ(degToRad(90)) *
                       Matrix44::Shift(0, -20, -4) *
                       Matrix44::Scale(1/200.0) *
                       Matrix44::RotationX(degToRad(90)));

        worldMesh->add(mesh, true);
        worldMesh->recomputeMeanNormals();

        worldMesh->dumpInfo();
    }


    double massOfCentralSphere = mass - 2 * massOfRotatingObjects - massOfTestingObject;
    Affine3DQ posOfCentralSphere = Affine3DQ(Vector3dd(0,0,0).normalised());
    double radiusOfCentralSphere = arm / 100;
    centralSphere = PhysSphere(&posOfCentralSphere, &radiusOfCentralSphere, &massOfCentralSphere);

    objects.push_back(&centralSphere);
    for (size_t i = 0; i < partsOfSystem.size(); ++i)
    {
        objects.push_back(&partsOfSystem[i]);
    }
}


void JanibekovsBolt::drawMyself(Mesh3D &mesh)
{
        mesh.mulTransform(getTransform());
        mesh.switchColor();
/*
        centralSphere.drawMesh(mesh);
        for (int i = 0; i < partsOfSystem.size(); i++) {
            partsOfSystem[i].drawMesh(mesh);
        }
*/
        for (size_t i = 0; i < objects.size(); i++) {
            objects[i]->drawMesh(mesh);
        }

        Circle3d circle;
        circle.c = Vector3dd(0,0,0);
        circle.r = 0.3;
        circle.normal = Vector3dd(1,0,0);
        mesh.addCircle(circle);
        mesh.currentColor = RGBColor::Violet();
        mesh.addLine(objects[3]->getPosVector(), objects[4]->getPosVector());
        mesh.addLine(objects[1]->getPosVector(), objects[2]->getPosVector());
        mesh.popTransform();
        mesh.currentColor = RGBColor::Cyan();
        drawForces(mesh);
}

void JanibekovsBolt::drawForces(Mesh3D &mesh)
{
    for (size_t i = 0; i < partsOfSystem.size(); i++)
    {
        Affine3DQ motorToWorld = getTransform() * partsOfSystem[i].getPosAffine();
        Vector3dd force = motorToWorld.rotor * partsOfSystem[i].getForce();
        Vector3dd motorPosition = motorToWorld.shift;
        Vector3dd startDot = motorPosition;
        Vector3dd endDot = motorPosition - force * 20.0;
        mesh.addLine(startDot, endDot);

        //L_INFO << "force: " << force << ", position " << motorPosition;
        //L_INFO << "Drew force line from: " << startDot << " , to: " << endDot << " ; Force value: " << force;
    }
}

Affine3DQ JanibekovsBolt::getTransform()
{
    return Affine3DQ(this->orientation, this->getPosCenter());
}

void JanibekovsBolt::drawMyself(Mesh3DDecorated &mesh)
{
    JanibekovsBolt::drawMyself((Mesh3D &)mesh);

    /* Scene should be drawed */

    //L_INFO << "Quad::drawMyself(Mesh3DDecorated &mesh): before\n";
    //mesh.dumpInfo();


    if (worldMesh != NULL)
    {
        mesh.add(*worldMesh);
    }


    //L_INFO << "Quad::drawMyself(Mesh3DDecorated &mesh): after\n";
    //mesh.dumpInfo();


}

void JanibekovsBolt::physicsTick(double deltaT)
{
    /*
    if(!testMode)
    {
        startTick();
        for (size_t i = 0; i < motors.size(); ++i) {
            motors[i].calcForce();
        }
    }
    */
    calcForce();
    calcMoment();

    /* TODO: Add air friction*/
    //addForce(Vector3dd(0.0, 0.0, -9.8 * getSystemMass()));
    tick(deltaT);

    /*TODO: Add real collistion comрutation */

    //cout << "Quad::physicsTick(): " << position << endl;
}




void JanibekovsBolt::tick(double deltaT)
{
    double radius = centralSphere.radius;
    double centerMass = centralSphere.mass;

    double massOfRotatingObjects = partsOfSystem[0].mass;
    double massOfTestingObject = partsOfSystem[2].mass;

    double armOfRotatingObjects = partsOfSystem[0].getPosVector().l2Metric();
    double armOfTestingObject = partsOfSystem[2].getPosVector().l2Metric();

    double inertialMomentX = 2.0 / 5.0 * centerMass * pow(radius, 2) + 2 * massOfRotatingObjects * pow(armOfRotatingObjects, 2);
    double inertialMomentY = 2.0 / 5.0 * centerMass * pow(radius, 2) + massOfTestingObject * pow(armOfTestingObject, 2);
    double inertialMomentZ = 2.0 / 5.0 * centerMass * pow(radius, 2) + 2 * massOfRotatingObjects * pow(armOfRotatingObjects, 2)
                                                                     + massOfTestingObject * pow(armOfTestingObject, 2);


    inertialMomentX = 0.001;
    inertialMomentY = 0.002;
    inertialMomentZ = 0.0001;

    Matrix33 diagonalizedInertiaTensor = Matrix33(inertialMomentX, 0, 0,
                                                  0, inertialMomentY, 0,
                                                  0, 0, inertialMomentZ);


    Matrix33 transposedOrient = orientation.toMatrix();
    transposedOrient.transpose();

    //inertiaTensor = orientation.toMatrix() * diagonalizedInertiaTensor * transposedOrient;// orientation.toMatrix().transpose();
inertiaTensor = diagonalizedInertiaTensor;
    /*
    if(testMode)
    {
        inertiaTensor = orientation.toMatrix() * diagonalizedInertiaTensor * transposedOrient;// orientation.toMatrix().transpose();
    }
    else
    {
        inertiaTensor = diagonalizedInertiaTensor;
    }
*/
    using namespace std::chrono;
    time_t ms0 = duration_cast< milliseconds >(
    system_clock::now().time_since_epoch()
    ).count();
    if(ms0 % 200 == 0)
    {
        Matrix33 invAngVel = angularVelocity.toMatrix();
        L_INFO << invAngVel;
        //L_INFO << orientation;
        //L_INFO<< "Diagonalized Tensor: " << diagonalizedInertiaTensor / inertialMomentX;
        //L_INFO << "Inertia tensor: " << inertiaTensor/inertialMomentX;
    }

    velocity = Vector3dd(0.0, 0.0, 0.0);

    Vector3dd newPos = getPosCenter() + velocity * deltaT;
    if (newPos.z() < -0.1)
    {
        velocity = Vector3dd::Zero();
        setPosCenter(Vector3dd(newPos.x(), newPos.y(), -0.1));
    }
    else {
        setPosCenter(newPos);
    }
    velocity += (getForce() / getSystemMass()) * deltaT;

    /* We should carefully use inertiaTensor here. It seems like it changes with the frame of reference */
    /**This works as wanted**/
    Vector3dd W = inertiaTensor.inv() * getMomentum();
    angularAcceleration = Quaternion::pow(Quaternion::Rotation(W, W.l2Metric()), 0.000001);

    Quaternion q = orientation;

    orientation = Quaternion::pow(angularVelocity, deltaT * 1000) ^ orientation;

    //Just async output
    using namespace std::chrono;
    time_t ms = duration_cast< milliseconds >(
    system_clock::now().time_since_epoch()
    ).count();
    if(ms % 200 == 0)
    {
        //L_INFO<<"Delta orient: "<<orientation.getAngle()-q.getAngle();
        //L_INFO << angularAcceleration;
    }

    //orientation.printAxisAndAngle();
    Quaternion temp = Quaternion::pow(angularAcceleration,deltaT);

    using namespace std::chrono;
    time_t ms1 = duration_cast< milliseconds >(
    system_clock::now().time_since_epoch()
    ).count();
    if(ms % 200 == 0)
    {
        //L_INFO << angularVelocity;
    }



    angularVelocity = Quaternion::pow(angularAcceleration, deltaT * 1000) ^ angularVelocity;

    //L_INFO<<"Delta orient: "<<abs(orientation.getAngle()-q.getAngle());

}
