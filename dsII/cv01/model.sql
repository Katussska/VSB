CREATE TABLE Student
(
    login         CHAR(6)
        CONSTRAINT Student_PK PRIMARY KEY,
    fname         VARCHAR(30) NOT NULL,
    lname         VARCHAR(50) NOT NULL,
    email         VARCHAR(50) NOT NULL,
    grade         INTEGER     NOT NULL,
    date_of_birth DATE        NOT NULL
);

CREATE TABLE Teacher
(
    login      CHAR(6)
        CONSTRAINT Teacher_PK PRIMARY KEY,
    fname      VARCHAR(30) NOT NULL,
    lname      VARCHAR(50) NOT NULL,
    department VARCHAR(50) NOT NULL
);

CREATE TABLE Course
(
    code          CHAR(11) PRIMARY KEY,
    name          VARCHAR(50) NOT NULL,
    capacity      INT         NOT NULL,
    teacher_login CHAR(6),
    CONSTRAINT Course_Teacher_FK FOREIGN KEY (teacher_login) REFERENCES Teacher (login)
);

CREATE TABLE StudentCourse
(
    student_login CHAR(6),
    course_code   CHAR(11),
    year          INT,
    CONSTRAINT StudentCourse_PK PRIMARY KEY (student_login, course_code, year),
    CONSTRAINT StudentCourse_Student_FK FOREIGN KEY (student_login) REFERENCES Student (login),
    CONSTRAINT StudentCourse_Course_FK FOREIGN KEY (course_code) REFERENCES Course (code)
);

