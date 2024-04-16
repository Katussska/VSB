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
	class BankTest {

		@Test
		void equalToNullTest() {
			assertNotEquals(new Bank("New Bank"), null);
		}


		@Test
		void sameNameTest() {
			assertEquals(new Bank("New Bank"), new Bank(String.format("%s %s", "New", "Bank")));
		}

		@Test
		void nullNamesTest() {
			assertEquals(new Bank(null), new Bank(null));
		}

		@Test
		void nullNameTest() {
			assertNotEquals(new Bank(null), new Bank("New Banks"));
		}

    @Test
    void sameAccountTest() {
      Bank d1 = new Bank("a");
      Bank d2 = new Bank("a");
      d1.add(new SavingsAccount(new Client("Jana", "Novakova"), 1));
      d2.add(new SavingsAccount(new Client("Jana", "Novakova"), 1));
      assertEquals(d1, d2);
    }

    @Test
    void sameAccount2Test() {
      Bank d1 = new Bank("a");
      Bank d2 = new Bank("a");
      d1.add(new SavingsAccount(new Client("Jana", "Novakova"), 1));
      d2.add(new SavingsAccount(new Client("Jana", "Novakova"), 1));
      d1.add(new PropertyChangeListener() {
        
        @Override
        public void propertyChange(PropertyChangeEvent evt) {
          
        }
      });
      assertEquals(d1, d2);
    }

		@Test
		void sameAccountsTest() {
			Bank d1 = new Bank("a");
			Bank d2 = new Bank("a");
			d1.add(new SavingsAccount(new Client("Jana", "Novakova"), 1));
			d1.add(new CreditAccount(new Client("Roman", "Bezpenez"), 10, 20));
			d2.add(new SavingsAccount(new Client("Jana", "Novakova"), 1));
			d2.add(new CreditAccount(new Client("Roman", "Bezpenez"), 10, 20));
			assertEquals(d1, d2);
		}

		@Test
		void sameAccountsDifferentOrderTest() {
			Bank d1 = new Bank("a");
			Bank d2 = new Bank("a");
			d1.add(new SavingsAccount(new Client("Jana", "Novakova"), 1));
			d1.add(new CreditAccount(new Client("Roman", "Bezpenez"), 10, 20));
			d2.add(new CreditAccount(new Client("Roman", "Bezpenez"), 10, 20));
			d2.add(new SavingsAccount(new Client("Jana", "Novakova"), 1));
			assertNotEquals(d1, d2);
		}

		@Test
		void moreAccountsTest() {
			Bank d1 = new Bank("a");
			Bank d2 = new Bank("a");
			d1.add(new SavingsAccount(new Client("Jana", "Novakova"), 1));
			d1.add(new CreditAccount(new Client("Roman", "Bezpenez"), 10, 20));
			d2.add(new SavingsAccount(new Client("Jana", "Novakova"), 1));
			d2.add(new CreditAccount(new Client("Roman", "Bezpenez"), 10, 20));
			d2.add(new CreditAccount(new Client("Roman", "Bezpenez"), 10, 20));
			assertNotEquals(d1, d2);
		}

		@Test
		void lessAccountsTest() {
			Bank d1 = new Bank("a");
			Bank d2 = new Bank("a");
			d1.add(new SavingsAccount(new Client("Jana", "Novakova"), 1));
			d1.add(new CreditAccount(new Client("Roman", "Bezpenez"), 10, 20));
			d1.add(new CreditAccount(new Client("Roman", "Bezpenez"), 10, 20));
			d2.add(new SavingsAccount(new Client("Jana", "Novakova"), 1));
			d2.add(new CreditAccount(new Client("Roman", "Bezpenez"), 10, 20));
			assertNotEquals(d1, d2);
		}

		@Test
		void sameHashCodeTest() {
			Bank d1 = new Bank("a");
			Bank d2 = new Bank("a");
			d1.add(new SavingsAccount(new Client("Jana", "Novakova"), 1));
			d1.add(new CreditAccount(new Client("Roman", "Bezpenez"), 10, 20));
			d2.add(new SavingsAccount(new Client("Jana", "Novakova"), 1));
			d2.add(new CreditAccount(new Client("Roman", "Bezpenez"), 10, 20));
			Set<Bank> set = new HashSet<>();
			set.add(d1);
			assertTrue(set.contains(d2));
		}
	}

	@Nested
	class AccountTest {

		@Test
		void notSameClientsTest() {
			assertNotEquals(new Client("Milan", "Penezokaz"), new Client("Michal", "Nemamradpenize"));
		}

		@Test
		void sameClientsTest() {
			assertEquals(new Client("Milan", "Penezokaz"), new Client("Milan", "Penezokaz"));
		}

		@Test
		void nullClientSavingsAccountSameTest() {
			assertEquals(new SavingsAccount(null, 10), new SavingsAccount(null, 10));
		}

		@Test
		void equalSavingsAccountToNullTest() {
			assertNotEquals(new SavingsAccount(null, 10), null);
		}

		@Test
		void reflexivitySavingsAccountSameTest() {
			SavingsAccount c1 = new SavingsAccount(new Client("Jana", "Novakova"), 10);
			assertEquals(c1, c1);
		}

		@Test
		void reflexivitySavingsAccountTest() {
			SavingsAccount c1 = new SavingsAccount(new Client("Jana", "Novakova"), 10);
			SavingsAccount c2 = new SavingsAccount(new Client("Jana", "Novakova"), 10);
			assertEquals(c1, c2);
		}

		@Test
		void notSameSavingsAccountTest() {
			SavingsAccount c1 = new SavingsAccount(new Client("Jana", "Novakova"), 20);
			SavingsAccount c2 = new SavingsAccount(new Client("Jana", "Novakova"), 10);
			assertNotEquals(c1, c2);
		}

		@Test
		void symentricSavingsAccountTest() {
			SavingsAccount c1 = new SavingsAccount(new Client("Jana", "Novakova"), 10);
			SavingsAccount c2 = new SavingsAccount(new Client("Jana", "Novakova"), 10);
			assertEquals(c1, c2);
			assertEquals(c2, c1);
		}

		@Test
		void sameHashCodeSavingsAccountTest() {
			SavingsAccount c1 = new SavingsAccount(new Client("Jana", "Novakova"), 10);
			SavingsAccount c2 = new SavingsAccount(new Client("Jana", "Novakova"), 10);
			Set<SavingsAccount> set = new HashSet<>();
			set.add(c1);
			assertTrue(set.contains(c2));
		}

		@Test
		void nullClientCreditAccountSameTest() {
			assertEquals(new CreditAccount(null, 10, 20), new CreditAccount(null, 10, 20));
		}

		@Test
		void equalCreditAccountToNullTest() {
			assertNotEquals(new CreditAccount(null, 10, 20), null);
		}

		@Test
		void reflexivityCreditAccountSameTest() {
			CreditAccount c1 = new CreditAccount(new Client("Jana", "Novakova"), 10, 20);
			assertEquals(c1, c1);
		}

		@Test
		void reflexivityCreditAccountTest() {
			CreditAccount c1 = new CreditAccount(new Client("Jana", "Novakova"), 10, 20);
			CreditAccount c2 = new CreditAccount(new Client("Jana", "Novakova"), 10, 20);
			assertEquals(c1, c2);
		}

		@Test
		void symentricCreditAccountTest() {
			CreditAccount c1 = new CreditAccount(new Client("Jana", "Novakova"), 10, 20);
			CreditAccount c2 = new CreditAccount(new Client("Jana", "Novakova"), 10, 20);
			assertEquals(c1, c2);
			assertEquals(c2, c1);
		}

		@Test
		void sameHashCodeCreditAccountTest() {
			CreditAccount c1 = new CreditAccount(new Client("Jana", "Novakova"), 10, 20);
			CreditAccount c2 = new CreditAccount(new Client("Jana", "Novakova"), 10, 20);
			Set<CreditAccount> set = new HashSet<>();
			set.add(c1);
			assertTrue(set.contains(c2));
		}

		@Test
		void nullClientCreditAccountMathSameTest() {
			assertEquals(new CreditAccountMath(null, 10, 30), new CreditAccountMath(null, 10, 30));
		}

		@Test
		void equalCreditAccountMathToNullTest() {
			assertNotEquals(new CreditAccountMath(null, 10, 30), null);
		}

		@Test
		void reflexivityCreditAccountMathSameTest() {
			CreditAccountMath c1 = new CreditAccountMath(new Client("Jana", "Novakova"), 10, 30);
			assertEquals(c1, c1);
		}

		@Test
		void reflexivityCreditAccountMathTest() {
			CreditAccountMath c1 = new CreditAccountMath(new Client("Jana", "Novakova"), 10, 30);
			CreditAccountMath c2 = new CreditAccountMath(new Client("Jana", "Novakova"), 10, 30);
			assertEquals(c1, c2);
		}

		@Test
		void symentricCreditAccountMathTest() {
			CreditAccountMath c1 = new CreditAccountMath(new Client("Jana", "Novakova"), 10, 30);
			CreditAccountMath c2 = new CreditAccountMath(new Client("Jana", "Novakova"), 10, 30);
			assertEquals(c1, c2);
			assertEquals(c2, c1);
		}

		@Test
		void sameHashCodeCreditAccountMathTest() {
			CreditAccountMath c1 = new CreditAccountMath(new Client("Jana", "Novakova"), 10, 30);
			CreditAccountMath c2 = new CreditAccountMath(new Client("Jana", "Novakova"), 10, 30);
			Set<CreditAccountMath> set = new HashSet<>();
			set.add(c1);
			assertTrue(set.contains(c2));
		}

		@Test
		void diffrentClassAccountsTest() {
			assertNotEquals(new SavingsAccount(new Client("Jan", "Novak"), 20), new CreditAccount(new Client("Jan", "Novak"), 20, 20));
		}

		@Test
		void diffrentClassAccountsTest2() {
			assertEquals(new CreditAccountMath(new Client("Jan", "Novak"), 20, 20), new CreditAccount(new Client("Jan", "Novak"), 20, 20));
		}

		@Test
		void symmetryCreditAccountMathTest() {
			assertEquals(new CreditAccountMath(new Client("Jan", "Novak"), 20, 20), new CreditAccount(new Client("Jan", "Novak"), 20, 20));
			assertEquals(new CreditAccount(new Client("Jan", "Novak"), 20, 20), new CreditAccountMath(new Client("Jan", "Novak"), 20, 20));
		}

	}

}
