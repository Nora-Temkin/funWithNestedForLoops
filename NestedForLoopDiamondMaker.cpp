// Playing with loops to draw shapes in *s


#include <iostream>
using namespace std;
#include <iomanip>

int main()
{
    // draw a hollow diamond
    const int MIN_HEIGHT = 3, MAX_HEIGHT = 42;
    int height = 0,
        centralRowNumber = 0,       // which row # is at the very center of the diamond?
        thickness = 0,
        maxOuterSpaces = 0,         // number of blank spaces to display before/after *s at very top & bottom of diamond
        outerSpacesThisRow = 0,     // actual number of outer blank spaces to display on current row
        maxInnerSpaces = 0,         // number of blank spaces to display between walls of diamond on center row
        innerSpacesThisRow = 0,     // actual number of inner blank spaces to display on current row
        rowCounter = 0,
        starCounter = 0,
        outerSpaceCounter = 0,      // could combine outer & inner space counters, but it would be harder
        innerSpaceCounter = 0;      // to trace for testing & debugging, and harder to maintain code later
    char yesOrNoResponse;
    bool filledSolid = false;       // if user wants a solid diamond, reset to true & display no inner spaces

    // Ask user for overall height of diamond; must be an odd # between 3 & 39
    do
    {
        cout << "Please enter an odd number between 3 & 39 (inclusive).\n"
            << "This number will be the overall height of your diamond: ";
        cin >> height;
    } while (height < 3 || height > 39 || (height % 2) == 0);
    centralRowNumber = (height / 2) + 1;

    // Ask user for thickness of diamond's walls; must be at least 1 & no more than half of height (rounded down)
    do
    {
        cout << "How thick do you want the walls of your diamond to be?\n"
            << "Please enter a whole number between 1 and " << (height / 2) << ": ";
        cin >> thickness;
    } while (thickness < 1 || thickness >(height / 2));
    maxOuterSpaces = (height / 2);  // odd height means this should truncate (round down) to allow 1 central star on top & bottom rows

    if (thickness == (height / 2))
    {
        cout << "Do you want your diamond to be filled solid with stars? (Y/N) ";
        cin >> yesOrNoResponse;
        if (yesOrNoResponse == 'Y' || yesOrNoResponse == 'y')
        {
            filledSolid = true;
            maxInnerSpaces = 0;
        }
        else
        {
            filledSolid = false;
            maxInnerSpaces = height - (thickness * 2);
        }
    }
    else
        maxInnerSpaces = height - (thickness * 2);

    // Set up inner & outer loops to display appropriate # of spaces & stars in diamond pattern
    cout << endl;       // blank line between user input & top of diamond

    // top half of diamond (above center row)
    outerSpacesThisRow = maxOuterSpaces;    // row 1 should have 1 single central * w/max outer spaces flanking it
    if (filledSolid == true)    // no inner spaces, just stars
    {
        for (rowCounter = 1; rowCounter < centralRowNumber; rowCounter++)
        {
            for (outerSpaceCounter = outerSpacesThisRow; outerSpaceCounter > 0; outerSpaceCounter--)    // blank spaces before stars
                cout << " ";
            for (starCounter = 0; starCounter < (height - (outerSpacesThisRow * 2)); starCounter++)     // centered stars
                cout << "*";
            for (outerSpaceCounter = 0; outerSpaceCounter < outerSpacesThisRow; outerSpaceCounter++)    // blank spaces after stars
                cout << " ";
            cout << endl;
            outerSpacesThisRow--;
        }
        if (rowCounter == centralRowNumber)     // central row = solid stars w/ no outer spaces flanking them
        {
            outerSpacesThisRow = 0;
            for (starCounter = 0; starCounter < height; starCounter++)
                cout << "*";
            cout << endl;
            rowCounter++;
            outerSpacesThisRow++;   // sets # of outer spaces flanking stars to 1 for next line displayed
        }

        for (rowCounter = (centralRowNumber + 1); rowCounter <= height; rowCounter++)   // bottom half of diamond w/outer spaces
        {
            for (outerSpaceCounter = 0; outerSpaceCounter < outerSpacesThisRow; outerSpaceCounter++)    // blank spaces before stars
                cout << " ";
            for (starCounter = 0; starCounter < (height - (outerSpacesThisRow * 2)); starCounter++)     // centered stars
                cout << "*";
            for (outerSpaceCounter = outerSpacesThisRow; outerSpaceCounter > 0; outerSpaceCounter--)    // blank spaces after stars
                cout << " ";

            cout << endl;
            outerSpacesThisRow++;
        }
    }
    else    // diamond is hollow, w/ blank spaces between walls of user-specified thickness
    {
        for (rowCounter = 1; rowCounter <= thickness; rowCounter++)   // above row where solid top splits into 2 walls
        {
            for (outerSpaceCounter = outerSpacesThisRow; outerSpaceCounter > 0; outerSpaceCounter--)
                cout << " ";
            for (starCounter = 0; starCounter < (height - 2 * outerSpacesThisRow); starCounter++)
                cout << "*";
            for (outerSpaceCounter = 0; outerSpaceCounter < outerSpacesThisRow; outerSpaceCounter++)
                cout << " ";

            cout << endl;
            outerSpacesThisRow--;
        }
        // top half of diamond, at & below row where solid row of stars splits into 2 walls of user-specified thickness each
        innerSpacesThisRow = 1;     // 1 blank space in center of 1st row where walls of diamond split apart
        for (rowCounter = (thickness + 1); rowCounter < centralRowNumber; rowCounter++)
        {
            for (outerSpaceCounter = outerSpacesThisRow; outerSpaceCounter > 0; outerSpaceCounter--)    // blank spaces before stars
                cout << " ";
            for (starCounter = 0; starCounter < thickness; starCounter++)                               // first wall of stars
                cout << "*";
            for (innerSpaceCounter = 0; innerSpaceCounter < innerSpacesThisRow; innerSpaceCounter++)    // blank spaces between walls
                cout << " ";
            for (starCounter = 0; starCounter < thickness; starCounter++)                               // second wall of stars
                cout << "*";
            for (outerSpaceCounter = 0; outerSpaceCounter < outerSpacesThisRow; outerSpaceCounter++)    // blank spaces after stars
                cout << " ";

            cout << endl;
            outerSpacesThisRow--;       // outer spaces flanking stars decrease as rows move toward widest center row
            innerSpacesThisRow += 2;     // width of central blank space increases by 2 spaces each row to maintain star spacing
        }

        // central row of diamond; no outer spaces; inner spaces at max. value
        if (rowCounter == centralRowNumber)     // center; if thickness = 1/2 of height, display 1 blank space
        {
            innerSpacesThisRow = maxInnerSpaces;
            for (starCounter = 0; starCounter < thickness; starCounter++)       // display first wall of stars
                cout << "*";
            for (innerSpaceCounter = 0; innerSpaceCounter < innerSpacesThisRow; innerSpaceCounter++)
                cout << " ";                                                    // display blank spaces in center of diamond
            for (starCounter = 0; starCounter < thickness; starCounter++)       // display second wall of stars
                cout << "*";

            cout << endl;   // advance to next row to start bottom half of diamond
            outerSpacesThisRow++;   // increase outer spaces to 1 for next row
        }

        // bottom half of diamond, above row where 2 walls of user-specified thickness each merge into solid stars

        innerSpacesThisRow -= 2;     // inner blank space decreases by 2 spaces from widest point on central row above

        for (rowCounter = (centralRowNumber + 1); rowCounter <= (height - thickness); rowCounter++)
        {
            for (outerSpaceCounter = 0; outerSpaceCounter < outerSpacesThisRow; outerSpaceCounter++)    // blank spaces before stars
                cout << " ";
            for (starCounter = 0; starCounter < thickness; starCounter++)                               // first wall of stars
                cout << "*";
            for (innerSpaceCounter = 0; innerSpaceCounter < innerSpacesThisRow; innerSpaceCounter++)    // blank spaces between walls
                cout << " ";
            for (starCounter = 0; starCounter < thickness; starCounter++)                               // second wall of stars
                cout << "*";
            for (outerSpaceCounter = outerSpacesThisRow; outerSpaceCounter > 0; outerSpaceCounter--)    // blank spaces after stars
                cout << " ";

            cout << endl;
            outerSpacesThisRow++;
            innerSpacesThisRow -= 2;
        }

        // bottom half of diamond, below where 2 walls merge into a single length of stars
        for (rowCounter = (height - thickness + 1); rowCounter <= height; rowCounter++)
        {
            for (outerSpaceCounter = 0; outerSpaceCounter < outerSpacesThisRow; outerSpaceCounter++)
                cout << " ";
            for (starCounter = 0; starCounter < (height - 2 * outerSpacesThisRow); starCounter++)
                cout << "*";
            for (outerSpaceCounter = outerSpacesThisRow; outerSpaceCounter > 0; outerSpaceCounter--)
                cout << " ";

            cout << endl;
            outerSpacesThisRow++;
        }
    }
    return 0;
}
