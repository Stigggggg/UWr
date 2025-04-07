class Student {
    void show() {
        usosWebPage.getStudentGradeInfo();
    }
}

class UsosWebPage {
    void getStudentGradeInfo() {
        gradeController.getCourses();
        for each course in courses {
            mark = course.getMark(student);
            mark.getValue();
        }
        pageLayout();
    }
}

class GradeController {
    List<Course> getCourses() {
        return student.getCourses();
    }
}

class Student {
    List<Course> getCourses() {
        return enrolledCourses;
    }
}

class Course {
    Mark getMark(Student student) {
        return student.getMark(this);
    }
}

class Mark {
    int getValue() {
        return value;
    }
}