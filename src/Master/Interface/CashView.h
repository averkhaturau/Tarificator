#ifndef __CASHVIEW_H__
#define __CASHVIEW_H__



// Predefinitions
class CInterfaceDoc;

class CCashView : public CScrollView
{
	private:
	protected:
		DECLARE_DYNCREATE(CCashView)
		DECLARE_MESSAGE_MAP()

		virtual void OnDraw(CDC* pDC);

		CInterfaceDoc* GetDocument();
	public:
		virtual void OnInitialUpdate();

		CCashView();
		virtual ~CCashView();
};


#endif // __CASHVIEW_H__