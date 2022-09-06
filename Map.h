#pragma once
#include "WorldTransform.h"
#include "Model.h"

class Map {
  public:
	~Map();
	void Initialize();
	void Update();
	void Draw(ViewProjection viewProjection);

  private:
	Model* model_ = nullptr;
	
	//�}�b�v�̗v�f��
	static const int xElement = 12;
	static const int yElement = 2;
	static const int zElement = 12;
	WorldTransform worldTransform_[xElement][yElement][zElement];

	//�}�b�v�`�b�v
	int mapchip[xElement][yElement][zElement];

	float modelSize = NULL;
};