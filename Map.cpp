#include"Map.h"
#include"Affine.h"

Map::~Map() {
	delete model_;
}

void Map::Initialize() {
//------------------���f������-----------------
	std::string a = "cube";
	model_ = Model::CreateFromOBJ(a, false);
	modelSize = 2;

//------------------���W�ݒ�-------------------
	for (int y = 0; y < yElement; y++) {
		for (int x = 0; x < xElement; x++) {
			for (int z = 0; z < zElement; z++) {
				worldTransform_[x][y][z].Initialize();
				//������0,0,0
				worldTransform_[x][y][z].translation_ = Vector3(
				  (x * modelSize) - (xElement * modelSize / 2),
				  (y * modelSize) - (yElement * modelSize / 2),
				  (z * modelSize) - (zElement * modelSize / 2));
				//�s��ݒ�
				Matrix4 matScale = AffineScale(worldTransform_[x][y][z]);
				Matrix4 matRotaX = AffineRotaX(worldTransform_[x][y][z]);
				Matrix4 matRotaY = AffineRotaY(worldTransform_[x][y][z]);
				Matrix4 matRotaZ = AffineRotaZ(worldTransform_[x][y][z]);
				Matrix4 matRota = AffineRota(matRotaZ, matRotaX, matRotaY);
				Matrix4 matTrans = AffineTrans(worldTransform_[x][y][z]);
				//�|��
				worldTransform_[x][y][z].matWorld_ = AffineWorld(matScale, matRota, matTrans);

				//�s��̓]��
				worldTransform_[x][y][z].TransferMatrix();
			}
		}
	}

//-----------�}�b�v�`�b�v�̓ǂݍ���-------------
	//���Œ��ڏ�������
	for (int y = 0; y < yElement; y++) {
		for (int x = 0; x < xElement; x++) {
			for (int z = 0; z < zElement; z++) {
				mapchip[x][y][z] = 1;
			}
		}
	}

	//�����ɓ���̏ꏊ�Ɍ���������
	//������0,0,0
	for (int x = 1; x < xElement - 1; x++) {
		for (int z = 1; z < xElement - 1; z++) {
			mapchip[x][1][z] = 0;
		}
	}

//---------------------------------------

}

void Map::Update() {

}

void Map::Draw(ViewProjection viewProjection) {
	for (int y = 0; y < yElement; y++) {
		for (int x = 0; x < xElement; x++) {
			for (int z = 0; z < zElement; z++) {
				if (mapchip[x][y][z] == 1) {
					model_->Draw(worldTransform_[x][y][z], viewProjection);
				}
			}
		}
	}
}