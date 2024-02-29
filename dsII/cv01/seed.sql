INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('smi324', 'Mary', 'Smith', 'smith@gmail.com', 1, to_date('1998/05/31', 'yyyy/mm/dd'));
INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('joh357', 'Patricia', 'Johnson', 'patricia.johnson@vsb.cz', 1, to_date('1997/09/23', 'yyyy/mm/dd'));
INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('wil986', 'Linda', 'Williams', 'williams.linda@tieto.com', 1, to_date('1998/02/02', 'yyyy/mm/dd'));
INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('jon067', 'Barbara', 'Jones', 'jones.barbara@tieto.com', 1, to_date('1997/12/12', 'yyyy/mm/dd'));
INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('bro654', 'Elizabeth', 'Brown', 'brown.elizabeth@tieto.com', 1, to_date('1998/06/06', 'yyyy/mm/dd'));
INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('gan098', 'James', 'Gannon', 'jimmyg@gmail.com', 1, to_date('1998/04/22', 'yyyy/mm/dd'));
INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('far483', 'John', 'Farnsworth', 'farnie@yahoo.com', 1, to_date('1998/04/02', 'yyyy/mm/dd'));
INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('bau764', 'Robert', 'Baughman', 'robert.baughman@vsb.cz', 2, to_date('1997/02/25', 'yyyy/mm/dd'));
INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('sil012', 'Michael', 'Silverman', 'silverman@gmail.com', 2, to_date('1997/03/15', 'yyyy/mm/dd'));
INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('sat767', 'William', 'Satterfield', 'satter@hotmail.com', 2, to_date('1996/11/11', 'yyyy/mm/dd'));
INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('rol087', 'David', 'Royal', 'david.royal@vsb.cz', 2, to_date('1996/10/12', 'yyyy/mm/dd'));
INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('mcc676', 'Richard', 'McCrary', 'mccrary@dell.com', 2, to_date('1996/12/20', 'yyyy/mm/dd'));
INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('kow007', 'Charles', 'Kowalski', 'charliw@yahoo.com', 3, to_date('1995/05/12', 'yyyy/mm/dd'));
INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('joy087', 'Joseph', 'Joy', 'joy@oracle@com', 3, to_date('1995/01/04', 'yyyy/mm/dd'));
INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('gri453', 'Thomas', 'Grigsby', 'thomas.grigsby@vsb.cz', 3, to_date('1994/09/27', 'yyyy/mm/dd'));
INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('gre227', 'Christopher', 'Greco', 'greco.gmail.com', 3, to_date('1994/11/07', 'yyyy/mm/dd'));
INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('cab466', 'Daniel', 'Cabral', 'daniel.cabral@vsb.cz', 4, to_date('1994/05/05', 'yyyy/mm/dd'));
INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('tro552', 'Paul', 'Trout', 'paul.trout@vsb.cz', 4, to_date('1993/11/29', 'yyyy/mm/dd'));
INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('rin766', 'Mark', 'Rinehard', 'rino@yahoo.com', 5, to_date('1992/04/10', 'yyyy/mm/dd'));
INSERT INTO Student (login, fname, lname, email, grade, date_of_birth)
VALUES ('pen048', 'Erika', 'Pena', 'erika.pena@vsb.cz', 5, to_date('1992/02/22', 'yyyy/mm/dd'));


INSERT INTO Teacher (login, fname, lname, department)
VALUES ('jor012', 'Jerry', 'Jordon', 'Department of Computer Science');
INSERT INTO Teacher (login, fname, lname, department)
VALUES ('gil233', 'Dennis', 'Gilman', 'Department of Computer Science');
INSERT INTO Teacher (login, fname, lname, department)
VALUES ('per085', 'Walter', 'Perryman', 'Department of Computer Science');
INSERT INTO Teacher (login, fname, lname, department)
VALUES ('new056', 'Patrick', 'Newsom', 'Department of Mathematic');
INSERT INTO Teacher (login, fname, lname, department)
VALUES ('men623', 'Peter', 'Menard', 'Department of Mathematic');
INSERT INTO Teacher (login, fname, lname, department)
VALUES ('mar118', 'Harold', 'Martino', 'Department of Management');
INSERT INTO Teacher (login, fname, lname, department)
VALUES ('gra198', 'Douglas', 'Graf', 'Department of Management');
INSERT INTO Teacher (login, fname, lname, department)
VALUES ('art035', 'Carl', 'Artis', 'Department of Management');


INSERT INTO Course (code, name, capacity, teacher_login)
VALUES ('460-ds1-011', 'Database Systems I', 5, 'jor012');
INSERT INTO Course (code, name, capacity, teacher_login)
VALUES ('460-ds2-012', 'Database Systems II', 5, 'jor012');
INSERT INTO Course (code, name, capacity, teacher_login)
VALUES ('460-cns-922', 'Computer Networks', 10, 'jor012');
INSERT INTO Course (code, name, capacity, teacher_login)
VALUES ('460-img-101', 'Image Processing', 5, 'jor012');
INSERT INTO Course (code, name, capacity, teacher_login)
VALUES ('460-jav-226', 'Java Technologies', 8, 'per085');
INSERT INTO Course (code, name, capacity, teacher_login)
VALUES ('460-pyt-001', 'Python', 10, 'per085');
INSERT INTO Course (code, name, capacity, teacher_login)
VALUES ('460-web-654', 'Web Technologies', 15, 'per085');
INSERT INTO Course (code, name, capacity, teacher_login)
VALUES ('470-alg-220', 'Algebra', 15, 'new056');
INSERT INTO Course (code, name, capacity, teacher_login)
VALUES ('470-dis-902', 'Discrete Math', 15, 'new056');
INSERT INTO Course (code, name, capacity, teacher_login)
VALUES ('420-mic-061', 'Microeconomics', 8, 'art035');
INSERT INTO Course (code, name, capacity, teacher_login)
VALUES ('420-mac-022', 'Macroeconomics', 8, 'art035');
INSERT INTO Course (code, name, capacity, teacher_login)
VALUES ('420-man-111', 'Management', 8, 'art035');
INSERT INTO Course (code, name, capacity, teacher_login)
VALUES ('420-toe-166', 'Theory of Economy', 15, 'art035');
INSERT INTO Course (code, name, capacity, teacher_login)
VALUES ('420-adv-061', 'Advertisement', 8, 'art035');

INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('smi324', '420-mic-061', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('smi324', '420-mac-022', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('smi324', '420-man-111', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('smi324', '420-toe-166', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('smi324', '420-adv-061', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('joh357', '420-mic-061', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('joh357', '420-mac-022', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('joh357', '420-man-111', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('wil986', '420-mic-061', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('wil986', '420-mac-022', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('jon067', '420-mic-061', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('jon067', '420-mac-022', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('jon067', '420-man-111', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('bro654', '420-mic-061', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('bro654', '420-mac-022', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('bro654', '420-man-111', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('gan098', '470-dis-902', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('far483', '470-dis-902', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('bau764', '460-ds1-011', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('sil012', '460-ds1-011', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('rol087', '460-ds1-011', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('mcc676', '470-alg-220', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('mcc676', '470-dis-902', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('kow007', '470-dis-902', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('gri453', '460-img-101', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('gre227', '460-img-101', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('cab466', '460-img-101', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('cab466', '460-jav-226', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('tro552', '460-img-101', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('tro552', '460-web-654', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('rin766', '460-web-654', 2020);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('smi324', '420-toe-166', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('smi324', '470-alg-220', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('smi324', '470-dis-902', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('joh357', '420-toe-166', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('joh357', '420-adv-061', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('joh357', '470-alg-220', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('joh357', '470-dis-902', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('wil986', '420-man-111', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('wil986', '420-toe-166', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('wil986', '420-adv-061', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('wil986', '470-alg-220', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('jon067', '420-man-111', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('jon067', '420-toe-166', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('bro654', '420-toe-166', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('bro654', '420-adv-061', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('bro654', '470-alg-220', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('bro654', '470-dis-902', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('gan098', '470-alg-220', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('gan098', '470-dis-902', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('gan098', '460-web-654', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('gan098', '420-toe-166', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('far483', '460-web-654', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('bau764', '470-dis-902', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('bau764', '460-ds2-012', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('sil012', '470-alg-220', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('sil012', '470-dis-902', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('sil012', '460-ds2-012', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('sat767', '470-alg-220', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('sat767', '470-dis-902', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('sat767', '460-web-654', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('mcc676', '470-dis-902', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('mcc676', '460-cns-922', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('mcc676', '460-web-654', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('mcc676', '420-toe-166', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('joy087', '470-alg-220', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('joy087', '470-dis-902', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('joy087', '460-cns-922', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('joy087', '460-web-654', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('joy087', '420-toe-166', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('joy087', '420-man-111', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('gri453', '470-dis-902', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('gri453', '460-cns-922', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('gri453', '460-img-101', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('gri453', '460-jav-226', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('gri453', '460-web-654', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('gri453', '470-alg-220', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('gre227', '470-alg-220', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('gre227', '470-dis-902', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('gre227', '460-cns-922', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('gre227', '460-web-654', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('cab466', '470-alg-220', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('cab466', '470-dis-902', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('cab466', '460-cns-922', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('cab466', '460-jav-226', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('cab466', '460-web-654', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('tro552', '470-alg-220', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('tro552', '470-dis-902', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('tro552', '460-cns-922', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('tro552', '460-img-101', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('tro552', '460-jav-226', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('tro552', '460-web-654', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('rin766', '470-dis-902', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('rin766', '460-cns-922', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('rin766', '460-img-101', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('rin766', '460-jav-226', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('rin766', '460-web-654', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('rin766', '470-alg-220', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('rin766', '420-toe-166', 2021);
INSERT INTO StudentCourse (student_login, course_code, year)
VALUES ('rin766', '420-man-111', 2021);