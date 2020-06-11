//author sbkun
#include <iostream>
#include <stdexcept>
#include <memory>
#include <string>

using namespace std;

enum class ColorType {
	Red,
	Blue
};

class Color {
	public:
		virtual ~Color() = default;
		virtual string dye() = 0;	
};

class Red: public Color {
	public:
		string dye() override {
			return "Red";
		}
};

class Blue: public Color {
	public:
		string dye() override {
			return "Blue";
		}
};

class Shape {
	public:
		Shape(ColorType color) {
			switch(color) {
				case ColorType::Red:
					color_.reset(new Red());
					break;
				case ColorType::Blue:
					color_.reset(new Blue());
					break;
				default:
					color_.reset(new Red());
			}
		}

		virtual ~Shape() = default;
		virtual void draw() = 0;

	protected:
		unique_ptr<Color>	color_;
};

class Circle: public Shape {
	public:
		using Shape::Shape; //使用父类构造函数
		void draw() override {
			cout<<"draw "<<"Circle and dye it "<<color_->dye()<<endl;
		}	
};

class Rectangle: public Shape {
	public:
		using Shape::Shape; //使用父类构造函数
		void draw() override {
			cout<<"draw "<<"Rectangle and dye it "<<color_->dye()<<endl;
		}	
};

int main(int argc, char* argv[]) {
	unique_ptr<Shape> circle(new Circle(ColorType::Red));
	unique_ptr<Shape> rectangle(new Rectangle(ColorType::Blue));
	circle->draw();
	rectangle->draw();
}
