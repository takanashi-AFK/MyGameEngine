
#include "GameObject.h"

class SceneManager : public GameObject
{
public:
	//�R���X�g���N�^
	//�����Fparent 
	SceneManager(GameObject* parent);

	~SceneManager();
	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};