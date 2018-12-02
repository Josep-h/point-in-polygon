# point-in-polygon

## Marks

This project starts with a test using techs of trangulating. But always save a polygon in a R-tree, and the point in R-tree two.

## Plan

### Trial One

Use the triangulation method to test the point-in-polygon in the following way:

1. Split the polygon into triangle and store the triangle with the polygon'id in a R*-tree.

2. So I need to develop a way to judge a point in a triangle which can be done in O(1)._(finished)_

3. Then I need to make a R*-tree to store my triangle which I will use a open sourse library of R*-tree. And the library will be tested before formally using.

4. Then the point-in-polygon test would be easy: Input a point and use the R*-tree to find rectangles that triangles produce and test if it's in the triangle. If yes, return the id of triangle which is same as the original polygon.

5. To delete a polygon, I need to figure out what are the triangles that the polygon keeps. So I need to build a Polygon class which keeps the rectangle that the triangles go into and it's id. Then remove the triangles with the id in the rectangle.

6. **Or?** In another way: Each polygon with splitted triangles form a tree it self, and the polygon form the R*-tree. When do test, we need to use the R*-tree to fetch the polygon and use the tree structure in polygon to get the triangle for test. To keep the complexity under _O(nlongn)_. To delete a polygon, I just need to remove the trangle with id that I give. The advantage of this method is that it done the clear work in one step which may cut the time which will be cost in the repeated work in former method.

## Stage One

Build the method for trangulating.
