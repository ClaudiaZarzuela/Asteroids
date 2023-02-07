#pragma once
class Image : public ecs::Component {
public:
	Image(Texture* tex) : //
		tr_(nullptr), //
		tex_(tex) {
	}
	virtual ~Image() …
		void initComponent() override;
	void render() override;
private:
	Transform* tr_;
	Texture* tex_;
};


