package cz.vsb.fei.java2.testhashcode;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.util.HashSet;
import java.util.Set;

import org.junit.jupiter.api.Nested;
import org.junit.jupiter.api.Test;

/**
 * Unit test for simple App.
 */
class AppTest {

	@Nested
	class DrawingTest {

		@Test
		void equalToNullTest() {
			assertNotEquals(new Drawing("New Drawing"), null);
		}


		@Test
		void sameNameTest() {
			assertEquals(new Drawing("New Drawing"), new Drawing(String.format("%s %s", "New", "Drawing")));
		}

		@Test
		void nullNamesTest() {
			assertEquals(new Drawing(null), new Drawing(null));
		}

		@Test
		void nullNameTest() {
			assertNotEquals(new Drawing(null), new Drawing("New Drawings"));
		}

    @Test
    void sameShapeTest() {
      Drawing d1 = new Drawing("a");
      Drawing d2 = new Drawing("a");
      d1.add(new Circle(new Point(0, 0), 1));
      d2.add(new Circle(new Point(0, 0), 1));
      assertEquals(d1, d2);
    }

    @Test
    void sameShape2Test() {
      Drawing d1 = new Drawing("a");
      Drawing d2 = new Drawing("a");
      d1.add(new Circle(new Point(0, 0), 1));
      d2.add(new Circle(new Point(0, 0), 1));
      d1.add(new PropertyChangeListener() {
        
        @Override
        public void propertyChange(PropertyChangeEvent evt) {
          
        }
      });
      assertEquals(d1, d2);
    }

		@Test
		void sameShapesTest() {
			Drawing d1 = new Drawing("a");
			Drawing d2 = new Drawing("a");
			d1.add(new Circle(new Point(0, 0), 1));
			d1.add(new Rectangle(new Point(1, -1), 10, 20));
			d2.add(new Circle(new Point(0, 0), 1));
			d2.add(new Rectangle(new Point(1, -1), 10, 20));
			assertEquals(d1, d2);
		}

		@Test
		void sameShapesDifferentOrderTest() {
			Drawing d1 = new Drawing("a");
			Drawing d2 = new Drawing("a");
			d1.add(new Circle(new Point(0, 0), 1));
			d1.add(new Rectangle(new Point(1, -1), 10, 20));
			d2.add(new Rectangle(new Point(1, -1), 10, 20));
			d2.add(new Circle(new Point(0, 0), 1));
			assertNotEquals(d1, d2);
		}

		@Test
		void moreShapesTest() {
			Drawing d1 = new Drawing("a");
			Drawing d2 = new Drawing("a");
			d1.add(new Circle(new Point(0, 0), 1));
			d1.add(new Rectangle(new Point(1, -1), 10, 20));
			d2.add(new Circle(new Point(0, 0), 1));
			d2.add(new Rectangle(new Point(1, -1), 10, 20));
			d2.add(new Rectangle(new Point(1, -1), 10, 20));
			assertNotEquals(d1, d2);
		}

		@Test
		void lessShapesTest() {
			Drawing d1 = new Drawing("a");
			Drawing d2 = new Drawing("a");
			d1.add(new Circle(new Point(0, 0), 1));
			d1.add(new Rectangle(new Point(1, -1), 10, 20));
			d1.add(new Rectangle(new Point(1, -1), 10, 20));
			d2.add(new Circle(new Point(0, 0), 1));
			d2.add(new Rectangle(new Point(1, -1), 10, 20));
			assertNotEquals(d1, d2);
		}

		@Test
		void sameHashCodeTest() {
			Drawing d1 = new Drawing("a");
			Drawing d2 = new Drawing("a");
			d1.add(new Circle(new Point(0, 0), 1));
			d1.add(new Rectangle(new Point(1, -1), 10, 20));
			d2.add(new Circle(new Point(0, 0), 1));
			d2.add(new Rectangle(new Point(1, -1), 10, 20));
			Set<Drawing> set = new HashSet<>();
			set.add(d1);
			assertTrue(set.contains(d2));
		}
	}
	
	@Nested
	class ShapeTest {

		@Test
		void notSamePointsTest() {
			assertNotEquals(new Point(10, -20), new Point(10, 20));
		}

		@Test
		void samePointsTest() {
			assertEquals(new Point(10, -20), new Point(10, -20));
		}

		@Test
		void nullPointCircleSameTest() {
			assertEquals(new Circle(null, 10), new Circle(null, 10));
		}

		@Test
		void equalCircleToNullTest() {
			assertNotEquals(new Circle(null, 10), null);
		}

		@Test
		void reflexivityCircleSameTest() {
			Circle c1 = new Circle(new Point(0, 0), 10);
			assertEquals(c1, c1);
		}

		@Test
		void reflexivityCircleTest() {
			Circle c1 = new Circle(new Point(0, 0), 10);
			Circle c2 = new Circle(new Point(0, 0), 10);
			assertEquals(c1, c2);
		}

		@Test
		void notSameCircleTest() {
			Circle c1 = new Circle(new Point(0, 0), 20);
			Circle c2 = new Circle(new Point(0, 0), 10);
			assertNotEquals(c1, c2);
		}

		@Test
		void symentricCircleTest() {
			Circle c1 = new Circle(new Point(0, 0), 10);
			Circle c2 = new Circle(new Point(0, 0), 10);
			assertEquals(c1, c2);
			assertEquals(c2, c1);
		}

		@Test
		void sameHashCodeCircleTest() {
			Circle c1 = new Circle(new Point(0, 0), 10);
			Circle c2 = new Circle(new Point(0, 0), 10);
			Set<Circle> set = new HashSet<>();
			set.add(c1);
			assertTrue(set.contains(c2));
		}

		@Test
		void nullPointRectangleSameTest() {
			assertEquals(new Rectangle(null, 10, 20), new Rectangle(null, 10, 20));
		}

		@Test
		void equalRectangleToNullTest() {
			assertNotEquals(new Rectangle(null, 10, 20), null);
		}

		@Test
		void reflexivityRectangleSameTest() {
			Rectangle c1 = new Rectangle(new Point(0, 0), 10, 20);
			assertEquals(c1, c1);
		}

		@Test
		void reflexivityRectangleTest() {
			Rectangle c1 = new Rectangle(new Point(0, 0), 10, 20);
			Rectangle c2 = new Rectangle(new Point(0, 0), 10, 20);
			assertEquals(c1, c2);
		}

		@Test
		void symentricRectangleTest() {
			Rectangle c1 = new Rectangle(new Point(0, 0), 10, 20);
			Rectangle c2 = new Rectangle(new Point(0, 0), 10, 20);
			assertEquals(c1, c2);
			assertEquals(c2, c1);
		}

		@Test
		void sameHashCodeRectangleTest() {
			Rectangle c1 = new Rectangle(new Point(0, 0), 10, 20);
			Rectangle c2 = new Rectangle(new Point(0, 0), 10, 20);
			Set<Rectangle> set = new HashSet<>();
			set.add(c1);
			assertTrue(set.contains(c2));
		}

		@Test
		void nullPointRectangleMathSameTest() {
			assertEquals(new RectangleMath(null, 10, 30), new RectangleMath(null, 10, 30));
		}

		@Test
		void equalRectangleMathToNullTest() {
			assertNotEquals(new RectangleMath(null, 10, 30), null);
		}

		@Test
		void reflexivityRectangleMathSameTest() {
			RectangleMath c1 = new RectangleMath(new Point(0, 0), 10, 30);
			assertEquals(c1, c1);
		}

		@Test
		void reflexivityRectangleMathTest() {
			RectangleMath c1 = new RectangleMath(new Point(0, 0), 10, 30);
			RectangleMath c2 = new RectangleMath(new Point(0, 0), 10, 30);
			assertEquals(c1, c2);
		}

		@Test
		void symentricRectangleMathTest() {
			RectangleMath c1 = new RectangleMath(new Point(0, 0), 10, 30);
			RectangleMath c2 = new RectangleMath(new Point(0, 0), 10, 30);
			assertEquals(c1, c2);
			assertEquals(c2, c1);
		}

		@Test
		void sameHashCodeRectangleMathTest() {
			RectangleMath c1 = new RectangleMath(new Point(0, 0), 10, 30);
			RectangleMath c2 = new RectangleMath(new Point(0, 0), 10, 30);
			Set<RectangleMath> set = new HashSet<>();
			set.add(c1);
			assertTrue(set.contains(c2));
		}

		@Test
		void diffrentClassShapesTest() {
			assertNotEquals(new Circle(new Point(10, 10), 20), new Rectangle(new Point(10, 10), 20, 20));
		}

		@Test
		void diffrentClassShapesTest2() {
			assertEquals(new RectangleMath(new Point(10, 10), 20, 20), new Rectangle(new Point(10, 10), 20, 20));
		}

		@Test
		void symmetryRectangleMathTest() {
			assertEquals(new RectangleMath(new Point(10, 10), 20, 20), new Rectangle(new Point(10, 10), 20, 20));
			assertEquals(new Rectangle(new Point(10, 10), 20, 20), new RectangleMath(new Point(10, 10), 20, 20));
		}

	}

}
