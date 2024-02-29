SELECT Student.fname, Student.lname, COUNT(StudentCourse.course_code) AS cnt
FROM Student
         LEFT JOIN StudentCourse ON Student.login = StudentCourse.student_login
WHERE Student.email LIKE '%vsb.cz'
GROUP BY Student.login, Student.fname, Student.lname;

WITH T AS
         (SELECT Teacher.fname, Teacher.lname, COUNT(Course.code) AS cnt
          FROM Teacher
                   LEFT JOIN Course ON Teacher.login = Course.teacher_login
          GROUP BY Teacher.login, Teacher.fname, Teacher.lname)
SELECT *
FROM T
WHERE cnt >= ALL (SELECT cnt FROM T);