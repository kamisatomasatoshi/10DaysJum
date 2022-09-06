#include"Player.h"
#include"Affine.h"

Player::~Player() {
	delete model_;
}

void Player::Initialize() {
//------------------���f������-----------------
	std::string a = "player";
	model_ = Model::CreateFromOBJ(a, false);

//--------���W�ݒ�------------
	worldTransform_.Initialize();

}

void Player::Entry(Input* input) {
	//���͂��ꂽ������z��̌��ɒǉ����Ă���
	if (input->TriggerKey(DIK_W)) {
		a.push_back(0);
	}
	if (input->TriggerKey(DIK_S)) {
		a.push_back(1);
	}
	if (input->TriggerKey(DIK_A)) {
		a.push_back(2);
	}
	if (input->TriggerKey(DIK_D)) {
		a.push_back(3);
	}
}

void Player::Move() {

	if (--moveTimer_ <= 0) {
		//���͂��ꂽ�L�[��񂪎c���Ă���Ȃ�
		if (!a.empty()) {
			//�z��̐擪�ɓ����Ă�������̏���
			if (a.front() == 0) {
				worldTransform_.translation_ += Vector3(0, 0, 2);
			}
			if (a.front() == 1) {
				worldTransform_.translation_ += Vector3(0, 0, -2);
			}
			if (a.front() == 2) {
				worldTransform_.translation_ += Vector3(-2, 0, 0);
			}
			if (a.front() == 3) {
				worldTransform_.translation_ += Vector3(2, 0, 0);
			}

			//�z��̐擪���폜
			a.erase(a.begin());
			
			//�^�C�}�[�̏�����
			moveTimer_ = moveTime;
		}
	}

	//�s��ݒ�
	Matrix4 matScale = AffineScale(worldTransform_);
	Matrix4 matRotaX = AffineRotaX(worldTransform_);
	Matrix4 matRotaY = AffineRotaY(worldTransform_);
	Matrix4 matRotaZ = AffineRotaZ(worldTransform_);
	Matrix4 matRota = AffineRota(matRotaZ, matRotaX, matRotaY);
	Matrix4 matTrans = AffineTrans(worldTransform_);
	//�|��
	worldTransform_.matWorld_ = AffineWorld(matScale, matRota, matTrans);

	//�s��̓]��
	worldTransform_.TransferMatrix();

}

void Player::Draw(ViewProjection viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
}