#include "WorldTransform.h"
#include"Affine.h"

void WorldTransform::Update() {
	//�s��v�Z
	matWorld_ = Affine();
	//�e�̍s����|����
	if (parent_ != NULL) {
		matWorld_ *= parent_->matWorld_;
	}
	//���[���h�s���]��
	TransferMatrix();
}