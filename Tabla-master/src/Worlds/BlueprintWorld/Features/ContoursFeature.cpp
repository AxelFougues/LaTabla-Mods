#include "../BlueprintWorld.h"

#ifdef isUsingContours


PolyLine2 BlueprintWorld::getContainerContour(vec2 point){
    const Contour* in = mContours.findLeafContourContainingPoint(point ,mContourFilter) ;
    if (in){
        return in->mPolyLine;
    }
    return getWorldBoundsPoly();
}

void BlueprintWorld::drawAllContours(Color color){
    ContourVector& contours = getContours();
    gl::color(color);
    for(Contour c : contours){
        if(c.mPolyLine.size()<CONTOUR_THRESHOLD)
            gl::draw(c.mPolyLine);
    }
}
void BlueprintWorld::drawWorldBounds(Color color){
    gl::color(color);
    gl::draw(getWorldBoundsPoly());
}
void BlueprintWorld::drawContainerContour(vec2 point, Color color){
    gl::color(color);
    gl::draw(getContainerContour(point));
}

void BlueprintWorld::reconCubeInputs(){
    cubeInputs.clear();
    for(Contour c : mContours){
        if(c.mIsLeaf && c.mPolyLine.getPoints().size()==4 && c.mArea < MAX_AREA_THRESHOLD){
            cubeInputs.push_back(c);
        }
    }
}

ColorA BlueprintWorld::getMeanContourColor(Contour c){
    Mat1b img = sourceImage->mImageCV.getMat(ACCESS_RW);
    rectangle(img, cv::Rect(0,0,100,100), Scalar(100), CV_FILLED);
    //Rectangle definition
    cv::Point pts[1][4];
    pts[0][0] = cv::Point(c.mPolyLine.getPoints()[0].x,c.mPolyLine.getPoints()[0].y);
    pts[0][1] = cv::Point(c.mPolyLine.getPoints()[0].x,c.mPolyLine.getPoints()[1].y);
    pts[0][2] = cv::Point(c.mPolyLine.getPoints()[0].x,c.mPolyLine.getPoints()[2].y);
    pts[0][3] = cv::Point(c.mPolyLine.getPoints()[0].x,c.mPolyLine.getPoints()[3].y);
    
    const cv::Point* points [1] = {pts[0]};
    int npoints = 4;
    
    //Mask creation
    Mat1b mask(img.rows, img.cols, uchar(0));
    fillPoly(mask, points, &npoints, 1, Scalar(255));
    
    //Mean color of crop
    Scalar average = mean(img);
    cout << average << endl;

    return ColorA(average.val[0]/255, average.val[1]/255, average.val[2]/255);
}


void BlueprintWorld::drawCubeInputs(Color color){
    gl::color(color);
    for(Contour c : cubeInputs){
        if(c.mPolyLine.size()<CONTOUR_THRESHOLD)
            gl::draw(c.mPolyLine);
        //gl::drawSolidRect(Rectf(c.mPolyLine.getPoints()));
    }
}
#endif
