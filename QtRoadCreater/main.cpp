#include "Forest.h"
#include <qDebug>

int main(int argc, char* argv[])
{
	Forest<int>	f;
	for (int i = 1; i < 14; ++i)
	{
		f.CreateNode(i);
	}

	f.CreateNode(1, 0, 0, 2);
	f.CreateNode(2, 0, 0, 3);
	f.CreateNode(3, 0, 4, 0);
	f.CreateNode(4, 0, 0, 6);
	f.CreateNode(6, 5, 7, 0);
	f.CreateNode(5, 0, 0, 1);
	f.CreateNode(7, 0, 0, 8);
	f.CreateNode(8, 0, 0, 9);
	f.CreateNode(9, 12, 0, 13);
	f.CreateNode(13, 0, 0, 9);
	f.CreateNode(12, 0, 0, 11);
	f.CreateNode(11, 0, 0, 10);
	f.CreateNode(10, 0, 0, 5);

	QString	str = "";

	std::list<MNode<int>> list = f.ReverseLevelTraversal(f.GetNode(5));

	for (std::list<MNode<int>>::iterator it = list.begin(); it != list.end(); ++it)
	{
		switch (it->type)
		{
		case ChildType::Child_Root:
			str += QString::fromLocal8Bit("[%1:%2]").arg(it->data).arg(QString::fromLocal8Bit("终止"));
			break;
		case ChildType::Child_Left:
			str += QString::fromLocal8Bit("[%1:%2]").arg(it->data).arg(QString::fromLocal8Bit("左转"));
			break;
		case ChildType::Child_Right:
			str += QString::fromLocal8Bit("[%1:%2]").arg(it->data).arg(QString::fromLocal8Bit("右转"));
			break;
		case ChildType::Child_Mid:
			str += QString::fromLocal8Bit("[%1:%2]").arg(it->data).arg(QString::fromLocal8Bit("直行"));
			break;
		}

	}

	qDebug() << "Level:\n" << str << endl;

	list = f.ReversePreTraversal(f.GetNode(5));

	str.clear();

	for (std::list<MNode<int>>::iterator it = list.begin(); it != list.end(); ++it)
	{
		switch (it->type)
		{
		case ChildType::Child_Root:
			str += QString::fromLocal8Bit("[%1:%2]").arg(it->data).arg(QString::fromLocal8Bit("终止"));
			break;
		case ChildType::Child_Left:
			str += QString::fromLocal8Bit("[%1:%2]").arg(it->data).arg(QString::fromLocal8Bit("左转"));
			break;
		case ChildType::Child_Right:
			str += QString::fromLocal8Bit("[%1:%2]").arg(it->data).arg(QString::fromLocal8Bit("右转"));
			break;
		case ChildType::Child_Mid:
			str += QString::fromLocal8Bit("[%1:%2]").arg(it->data).arg(QString::fromLocal8Bit("直行"));
			break;
		}
	}

	qDebug() << "PreOrder:\n" << str << endl;

	list = f.ReversePostTraversal(f.GetNode(5));

	str.clear();

	for (std::list<MNode<int>>::iterator it = list.begin(); it != list.end(); ++it)
	{
		switch (it->type)
		{
		case ChildType::Child_Root:
			str += QString::fromLocal8Bit("[%1:%2]").arg(it->data).arg(QString::fromLocal8Bit("终止"));
			break;
		case ChildType::Child_Left:
			str += QString::fromLocal8Bit("[%1:%2]").arg(it->data).arg(QString::fromLocal8Bit("左转"));
			break;
		case ChildType::Child_Right:
			str += QString::fromLocal8Bit("[%1:%2]").arg(it->data).arg(QString::fromLocal8Bit("右转"));
			break;
		case ChildType::Child_Mid:
			str += QString::fromLocal8Bit("[%1:%2]").arg(it->data).arg(QString::fromLocal8Bit("直行"));
			break;
		}
	}

	qDebug() << "PostOrder:\n" << str << endl;

	return 0;
}
