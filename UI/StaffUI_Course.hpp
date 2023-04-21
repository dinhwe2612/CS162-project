#ifndef StaffUI_Course_hpp
#define StaffUI_Course_hpp

#include "../external/raylib/src/raylib.h"
#include "Button.hpp"
#include "InputBar.hpp"
#include <array>
#include "../Header/view.h"
#include "../Header/SemesterCourse.h"

struct Course 
{
    int windowWidth, windowHeight;

    Texture2D background;
    
    Button close;
    Button addCourse;
    Button addCourseClose;
    Button Create;
    Button viewGPA;
    Button del, drop, add, back, info, delStudent, exportStudent, studentConfig;


    Font PT_serif_bold;
    Font PT_serif_regular;

    InputBar courseName;
    InputBar courseID;
    InputBar className;
    InputBar teacherName;
    InputBar numberOfCredits;
    InputBar maxStudents;
    
    InputBar enterClass;

    bool isAddCourse = false;

    // std::array <std::string, 10> ListOfCourses = {"CS161", "PH211", "MTH251", "CS162", "PH212", "MTH252", "CM101"};
    ACourse *ListOfCourses;
    int listCourseSize = 0;
    
    ACourse curCourse;

    Student *ListOfStudents;
    int listStudentSize = 0;
    
    bool courseClicked = false;
    int courseIndex;

    std::string dayLabel[7] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
    bool isDayChosen[7] = {true, false, false, false, false, false, false};

    std::string sessionLabel[4] = {"S1", "S2", "S3", "S4"};
    bool isSessionChosen[4] = {true, false, false, false};

    int menuCourse = -1;
    enum WindowCourse {
        CREATECOURSE,
        VIEWCOURSE,
        VIEWGPA,
        MODIFYCOURSE,
        ADDSTUDENT,
        IMPORTSTUDENTLIST,
        EXPORTSTUDENTLIST
    };

    string schoolYear;
    string semester;

    void Construct(int windowwidth, int windowHeight);
    void Deconstruct();

    std::string buttonChosen(float x, float y, float width, float height, std::string* labels, bool* isButtonPressed, int size);

    void Draw();
        void DrawBackground();
        void DrawCourseList();
        void DrawCreateCourse();
        void DrawModifyCourse();
        void DrawViewCourse();
        void ChooseViewClass();
        void DrawViewGPA();
        void DrawStudentList();
        void DrawAddStudent();
        void DrawImportStudentList();
        void DrawExportStudentList();
        void DrawDeleteStudent();
};

#endif