/**
 * \file main_test_convexHull2d.cpp
 * \brief This is the main file for the test convexHull2d 
 *
 * \date июн 01, 2018
 * \author alexander
 *
 * \ingroup autotest  
 */

#include <iostream>
#include "gtest/gtest.h"

#include "core/utils/global.h"
#include "core/geometry/polygons.h"
#include "core/geometry/convexHull.h"
#include "core/buffers/rgb24/rgbColor.h"
#include "core/buffers/rgb24/rgb24Buffer.h"
#include "core/buffers/bufferFactory.h"


using namespace std;
using namespace corecvs;

void drawPolygon2Color(RGB24Buffer *target, const Polygon &p, RGBColor color1, RGBColor color2);


TEST(ConvexHull, testConvexHull1)
{
    Polygon  p;
    p.push_back(Vector2dd(0.0, 0.0));
    p.push_back(Vector2dd(2.0, 0.0));
    p.push_back(Vector2dd(2.0, 4.0));
    p.push_back(Vector2dd(4.0, 4.0));
    p.push_back(Vector2dd(4.0, 0.0));
    p.push_back(Vector2dd(6.0, 0.0));
    p.push_back(Vector2dd(6.0, 6.0));
    p.push_back(Vector2dd(0.0, 6.0));

    /* Test Gift Wrap */
    Polygon result1 = ConvexHull::GiftWrap(p);
    cout << result1 << endl;
    for (size_t i = 0; i < result1.size(); i++)
    {
        Vector2dd point = result1[i];
        bool perefery = !point.isInRect(Vector2dd(0.01,0.01), Vector2dd(5.99,5.99));
        CORE_ASSERT_TRUE(perefery, "GiftWrap: Convex hull is wrong");
    }

    /* Test GrahamScan */
    Polygon pCopy(p);
    Polygon result2 = ConvexHull::GrahamScan(pCopy);
    cout << result2 << endl;
    for (size_t i = 0; i < result2.size(); i++)
    {
        Vector2dd point = result2[i];
        bool perefery = !point.isInRect(Vector2dd(0.01,0.01), Vector2dd(5.99,5.99));
        CORE_ASSERT_TRUE(perefery, "GrahamScan: Convex hull is wrong");
    }

    /* Test GrahamScan projective*/
    ProjectivePolygon pCopy1(p);
    ProjectivePolygon result3 = ConvexHull::GrahamScan(pCopy1);
    cout << result3 << endl;
    for (size_t i = 0; i < result3.size(); i++)
    {
        Vector2dd point = result3[i].normalisedProjective().xy();
        bool perefery = !point.isInRect(Vector2dd(0.01,0.01), Vector2dd(5.99,5.99));
        CORE_ASSERT_TRUE(perefery, "GrahamScan Projective: Convex hull is wrong");
    }

}

TEST(ConvexHull, testConvexHull2)
{
    std::vector<Vector2dd> points;

    double radius = 1.0;
    double eps = 1e-6;
    size_t N = 10;
    for (size_t i = 0; i < N; i++)
    {
        double angle = 2*M_PI/N*i;
        points.emplace_back(radius*std::cos(angle), radius*std::sin(angle));
    }

    std::vector<Vector2dd> pointsCopy(points);
    Polygon p1 = ConvexHull::GrahamScan(pointsCopy);
    ASSERT_TRUE(p1.size() == N);
    ASSERT_TRUE(p1.isConvex());

    Polygon p2 = ConvexHull::GiftWrap(points);
    ASSERT_TRUE(p2.size() == N);
    ASSERT_TRUE(p2.isConvex());

    ProjectivePolygon ppoints(points);
    ProjectivePolygon pp3 = ConvexHull::GrahamScan(ppoints);
    ASSERT_TRUE(pp3.size() == N);
    Polygon p3 = pp3.getApproximation(1.0);
    ASSERT_TRUE(p3.isConvex());


    for (size_t i = 0; i < N; i++)
    {
        double angle = 2*M_PI/N*i;
        double rho = radius*(1.0 - eps);
        Vector2dd point = Vector2dd(rho*std::cos(angle), rho*std::sin(angle));
        ASSERT_TRUE(p1.isInsideConvex(point));
        ASSERT_TRUE(p2.isInsideConvex(point));
        ASSERT_TRUE(p3.isInsideConvex(point));
    }

    for (size_t i = 0; i < N; i++)
    {
        double angle = 2*M_PI/N*i;
        double rho = radius*(1.0 + eps);
        Vector2dd point = Vector2dd(rho*std::cos(angle), rho*std::sin(angle));
        ASSERT_FALSE(p1.isInsideConvex(point));
        ASSERT_FALSE(p2.isInsideConvex(point));
        ASSERT_FALSE(p3.isInsideConvex(point));
    }


}



TEST(ConvexHull, testConvexHull3)
{
    std::vector<Vector2dd> points = {{640, 120}, {320, 240}
 , {640, 120} , {640, 120}
 , {640, 360} , {640, 360}
 , {640, 360} , {640, 355.2}
 , {640, 355.2} , {640, 350.4}
 , {640, 350.4} , {640, 345.6}
 , {640, 345.6} , {640, 340.8}
 , {640, 340.8} , {640, 336}
 , {640, 336} , {640, 331.2}
 , {640, 331.2} , {640, 326.4}
 , {640, 326.4} , {640, 321.6}
 , {640, 321.6} , {640, 316.8}
 , {640, 316.8} , {640, 312}
 , {640, 312} , {640, 307.2}
 , {640, 307.2} , {640, 302.4}
 , {640, 302.4} , {640, 297.6}
 , {640, 297.6} , {640, 292.8}
 , {640, 292.8} , {640, 288}
 , {640, 288} , {640, 283.2}
 , {640, 283.2} , {640, 278.4}
 , {640, 278.4} , {640, 273.6}
 , {640, 120} , {640, 120}
 , {640, 120}};

    std::vector<Vector2dd> pointsCopy(points);
    Polygon p1 = ConvexHull::GrahamScan(pointsCopy);
    //ASSERT_TRUE(p1.size() == N);
    cout << p1 << endl;
    cout << "Convex :" << (p1.isConvex() ? "true" : "false") << endl;
    ASSERT_TRUE(p1.isConvex());

    RGB24Buffer buffer(1000,1000);
    drawPolygon2Color(&buffer, p1, RGBColor::Blue(), RGBColor::Red());
    for (size_t id = 0; id < points.size(); id++)
    {
        buffer.drawCrosshare1(points[id].x(), points[id].y(), RGBColor:: White());
    }

    BufferFactory::getInstance()->saveRGB24Bitmap(buffer, "triangle.bmp");

}


TEST(ConvexHull, nonEigen)
{
    std::vector<Vector3dd> circle;

    double radius = 100.0;
    size_t N = 10;
    for (size_t i = 0; i < N; i++)
    {
        double angle = 2 * M_PI / N * i;
        circle.emplace_back(radius*std::cos(angle), radius*std::sin(angle), 1.0);
    }

    RGB24Buffer buffer(1000, 1500);

    {
        std::vector<Vector3dd> points = circle;
        points.emplace_back(1,0,0);
        ProjectivePolygon ppoints = points;
        ProjectivePolygon pp3 = ConvexHull::GrahamScan(ppoints);

        cout << pp3 << endl;
        ProjectivePolygon td = pp3.transformed(Matrix33::ShiftProj(750, 250));
        drawPolygon2Color(&buffer, td.getApproximation(1000000), RGBColor::Green(), RGBColor::Red());
    }

    {
        std::vector<Vector3dd> points = circle;
        points.emplace_back(-1,0,0);
        ProjectivePolygon ppoints = points;
        ProjectivePolygon pp3 = ConvexHull::GrahamScan(ppoints);

        cout << pp3 << endl;
        ProjectivePolygon td = pp3.transformed(Matrix33::ShiftProj(250, 250));
        drawPolygon2Color(&buffer, td.getApproximation(1000000), RGBColor::Green(), RGBColor::Red());
    }

    {
        std::vector<Vector3dd> points = circle;
        points.emplace_back(0,-1,0);
        ProjectivePolygon ppoints = points;
        ProjectivePolygon pp3 = ConvexHull::GrahamScan(ppoints);

        cout << pp3 << endl;
        ProjectivePolygon td = pp3.transformed(Matrix33::ShiftProj(750, 750));
        drawPolygon2Color(&buffer, td.getApproximation(1000000), RGBColor::Green(), RGBColor::Red());
    }

    {
        std::vector<Vector3dd> points = circle;
        points.emplace_back(0,1,0);
        ProjectivePolygon ppoints = points;
        ProjectivePolygon pp3 = ConvexHull::GrahamScan(ppoints);

        cout << pp3 << endl;
        ProjectivePolygon td = pp3.transformed(Matrix33::ShiftProj(250, 750));
        drawPolygon2Color(&buffer, td.getApproximation(1000000), RGBColor::Green(), RGBColor::Red());
    }

    {
        std::vector<Vector3dd> points = circle;
        points.emplace_back( 0, 1, 0);
        points.emplace_back( 0,-1, 0);
        points.emplace_back( 1, 0, 0);

        ProjectivePolygon ppoints = points;
        ProjectivePolygon pp3 = ConvexHull::GrahamScan(ppoints);

        cout << pp3 << endl;
        ProjectivePolygon td = pp3.transformed(Matrix33::ShiftProj(1250, 250));
        drawPolygon2Color(&buffer, td.getApproximation(1000000), RGBColor::Green(), RGBColor::Red());
    }



    BufferFactory::getInstance()->saveRGB24Bitmap(buffer, "non_eigen.bmp");

//    ASSERT_TRUE(pp3.size() == N);
//    Polygon p3 = pp3.getApproximation(1.0);
//    ASSERT_TRUE(p3.isConvex());

}





TEST(ConvexHull, wrapClose)
{
    /*creates a circle of points and a slightly smaller circle inside*/
    std::vector<Vector2dd> points;

    double radius = 1.0;
    double eps = 1e-6;
    size_t N = 10;
    for (size_t i = 0; i < N; i++)
    {
        double angle = 2 * M_PI / N * i;
        points.emplace_back(radius*std::cos(angle), radius*std::sin(angle));
    }

    for (size_t i = 0; i < N; i++)
    {
        double angle = 2 * M_PI / N * i;
        double rho = radius * (1.0 - eps);
        points.emplace_back(rho*std::cos(angle), rho*std::sin(angle));
    }

    std::vector<Vector2dd> pointsCopy(points);
    Polygon p1 = ConvexHull::GrahamScan(pointsCopy);
    ASSERT_EQ(p1.size(), N);
    ASSERT_TRUE(p1.isConvex());

    Polygon p2 = ConvexHull::GiftWrap(points);
    ASSERT_TRUE(p2.size() == N);
    ASSERT_TRUE(p2.isConvex());


    for (size_t i = 0; i < N; i++)
    {
        double angle = 2 * M_PI / N * i;
        double rho = radius * (1.0 - eps);
        Vector2dd point = Vector2dd(rho*std::cos(angle), rho*std::sin(angle));
        ASSERT_TRUE(p1.isInsideConvex(point));
        ASSERT_TRUE(p2.isInsideConvex(point));
    }

    for (size_t i = 0; i < N; i++)
    {
        double angle = 2 * M_PI / N * i;
        double rho = radius * (1.0 + eps);
        Vector2dd point = Vector2dd(rho*std::cos(angle), rho*std::sin(angle));
        ASSERT_FALSE(p1.isInsideConvex(point));
        ASSERT_FALSE(p2.isInsideConvex(point));
    }
}
