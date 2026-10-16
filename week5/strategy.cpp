#include <iostream>
#include <format>

class PaymentStrategy {
public:
	virtual void pay(double amount) const = 0;
};

class CashPayment : public PaymentStrategy {
public:
	void pay(double amount) const override {
		std::cout << std::format("Pay {} using cash\n", amount);
		// connect to credit card server and etc...
	}
};

class CreditCardPayment : public PaymentStrategy {
public:
	void pay(double amount) const override {
		std::cout << std::format("Pay {} using credit card\n", amount);
		// connect to credit card server and etc...
	}
};

class BitcoinPayment : public PaymentStrategy {
public:
	void pay(double amount) const override {
		//
	}
};

class ShoppingCard {
private:
	PaymentStrategy* payment_strategy_;
public:
	void set_payment(PaymentStrategy* payment_strategy) {
		payment_strategy_ = payment_strategy;
	}
	void checkout(double amount) {
		payment_strategy_->pay(amount);
	}
};
