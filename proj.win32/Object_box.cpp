//#include "Object_Box.h"
//
//extern Node* Game_Mode;
//
//
//
//bool Object_Box::Add_obj(Object_Scene* all_node)
//{
//	my_obj.push_back(all_node);
//	return true;
//}
//
//swich_node Object_Box::draw()
//{
//	if (Custom_Node != nullptr)
//	{
//		Custom_Node->removeFromPhysicsWorld();
//		Custom_Node = nullptr;
//	}
//	if (Custom_Node_old != nullptr)
//	{
//		Custom_Node_old->removeFromPhysicsWorld();
//		Custom_Node_old = nullptr;
//	}
//
//		Custom_Node = Node::create();
//		Custom_Node_old = Node::create();
//		Custom_Node->setTag(Custom_Tag);
//		Custom_Node_old->setTag(Custom_Tag_old);
//		Custom_Node->setOpacity(0);
//		this->my_node = Custom_Node;
//
//		for (int n = 0; n < my_obj.size(); n++)// ������ � ��������� ��� ����� � ��������� ��������� ����
//		{
//			auto data = my_obj[n]->draw();// �������� �� ����
//			data.old_ptr->removeFromParent();// ���������� �� ����
//			data.new_ptr->removeFromParent();// ���������� �� ����
//			Custom_Node_old->addChild(data.old_ptr);// ����������� ������ � ����
//			Custom_Node->addChild(data.new_ptr); //� ����������� � ����� ����
//		}
//		
//
//
//		Game_Mode->addChild(Custom_Node); //��������� ������ ���� �� ������
//		Game_Mode->addChild(Custom_Node_old);// � �� ������� ���������
//
//
//		return swich_node{ Custom_Node_old, Custom_Node };
//	
//}